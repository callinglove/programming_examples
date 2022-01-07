# -*- coding: utf-8 -*-
# @Time    : 2020/1/17 09:08  
# @File    : novel_crawler.py


import os
import re
import json
import time
import logging
from urllib.parse import urljoin
from collections import namedtuple
from bs4 import BeautifulSoup
import requests
from requests.packages.urllib3.exceptions import InsecureRequestWarning

requests.packages.urllib3.disable_warnings(InsecureRequestWarning)

Chapter = namedtuple('Chapter', ['idx', 'url', 'title'])

class NovelCrawler():
    def __init__(self, url):
        self.url = url
        self.novel_title = ''
        self.chapters = []

    def _get_html_content(self, url):
        """获取网页的html内容
           url:目标url地址
           content:返回的页面内容
       """
        headers = {
            "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/66.0.3359.139 Safari/537.36"
        }
        response = None
        try_time = 2
        for _ in range(try_time):
            response = requests.get(url, headers=headers, verify=False)
            if response.status_code  == 200:
                break
        response.encoding = response.apparent_encoding
        return response.text

    def get_chapters(self):
        index_content = self._get_html_content(self.url)

        # 先构建一个soup对象
        soup = BeautifulSoup(index_content, "lxml")
        # 获取小说的标题
        self.novel_title = soup.title.string
        # 找到小说的内容（是在div标签里面，并且这个div标签的id为"list"）
        content = soup.find("div", id="list")
        # 获取章节列表,列表里面的内容都是标签对象
        chapter_list = content.find_all("a", attrs={"style": "", "href": re.compile(r"/.*\.html")})
        # 定义一个空的字典，用于存放章节名称和对应url的键值对
        for idx, x in enumerate(chapter_list, start = 1):
            chapter = Chapter(idx, urljoin(self.url, x.attrs["href"]), x.string)
            self.chapters.append(chapter)

    def get_text(self):
        for chapter in self.chapters:
            if os.path.exists(str(chapter.idx)+".txt"):
                continue
            print(chapter)
            # time.sleep(5)
            try:
                chapter_content = self._get_html_content(chapter.url)
                soup_text = BeautifulSoup(chapter_content, "lxml")
                chapter_content = soup_text.find("div", id="content")
                if chapter_content is None:
                    continue

                # 获取soup对象中的文本信息text
                chapter_content = chapter_content.get_text()
                # 调用写入本地的函数
                self.save_chapter_content(chapter, chapter_content)
            except Exception as e:
                logging.exception(e)
                self.save_status()
                break

    def save_chapter_content(self, chapter, chapter_content):
        with open(str(chapter.idx)+".txt", 'a', encoding='utf-8') as f:
            f.write("\n" + chapter.title + "\n")
            f.write(chapter_content)
        print("\r%s 下载完毕!" % chapter.title)

    def save_status(self):
        with open('novel_cache.json','w', encoding='utf-8') as fw:
            json.dump(
                {"url": self.url, "novel_title": self.novel_title, "chapters": self.chapters},
                fw,
                ensure_ascii=False,
                indent=4
            )

    def load_status(self):
        if not os.path.exists("novel_cache.json"):
            return False

        data = None
        with open('novel_cache.json','r', encoding='utf-8') as fp:
            data = json.load(fp)
        if data.get("url", "") != self.url:
            return False

        self.novel_title = data.get("novel_title", "不知道哈")
        for chapter in data.get("chapters", []):
            if len(chapter) != len(Chapter._fields):
                self.chapters.clear()
            self.chapters.append(Chapter(*chapter))

        return True

    def run(self):
        if not self.load_status():
            self.get_chapters()
        self.get_text()

    
def main():  
    crawler = NovelCrawler("https://www.ddxs.cc/ddxs/188074/")
    crawler.run()
    
    
if __name__ == "__main__":  
    main()  
