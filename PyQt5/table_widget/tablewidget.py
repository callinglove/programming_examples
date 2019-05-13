from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
import res
import sys

class TableWidget(QTableWidget):

    def __init__(self,parent=None):
        super(TableWidget, self).__init__(parent)

        # 设置标题
        self.setWindowTitle("表格实例")
        # 设置logo
        self.setWindowIcon(QIcon(":/res/images/logo.png"))
        # 设置窗口大小
        self.resize(920, 240)

        self.setColumnCount(5)
        # setHorizontalHeaderLabels之前必须设置列数，否则设置失效
        self.setHorizontalHeaderLabels(["Name", "Sex", "Birthday", "Profession", "Salary"])
        header_view = self.horizontalHeader()
        header_view.setFont(QFont("song", 12, QFont.Bold))
        # header_view.setStretchLastSection(True)
        # header_view.setDefaultSectionSize(120)
        # header_view.resizeSection(0,150)
        header_view.setMaximumSectionSize(200)
        header_view.setMinimumSectionSize(100)
        header_view.setSectionResizeMode(QHeaderView.ResizeToContents)
        self.setStyleSheet("QHeaderView::section{background:skyblue;}")

        # with open("res/qss/table_widget.qss") as fd:
            # stylesheet = fd.read()
            # self.setStyleSheet(stylesheet)

        # self.setRowCount(2)
        
        # self.setColumnWidth(0, 200)
        # self.setColumnWidth(4, 200)
        # 设置行高
        # self.setRowHeight(0, 100)
        #设置第一行高度为100px，第一列宽度为200px。
        self.setVerticalHeaderLabels(["第一列", "第二列"])

        self.add_row_data("新海诚", "male", "2018/02/02", "Engineer", 16000)

    def add_row_data(self, name, sex, birthday, profession, salary):
        row = self.rowCount()
        self.insertRow(row)

        # 性别图片
        self.sex_pixmax = {
            "male": ":/res/images/male.png",
            "female": ":/res/images/female.png"
        }
        lbp = QLabel()
        lbp.setPixmap(QPixmap(self.sex_pixmax[sex]).scaled(30,30))
        self.setCellWidget(row,1,lbp)
        
        # 姓名item，设置字体
        twi = QTableWidgetItem(name)
        twi.setFont(QFont("Times", 10, ))
        self.setItem(row,0,twi)

        # 弹出日期选择，默认值为当前日期，显示格式年月日
        dte = QDateTimeEdit()
        dte.setDate(QDate.fromString(birthday, "yyyy/MM/dd") if birthday else QDate.currentDate())
        dte.setDisplayFormat("yyyy/MM/dd")
        dte.setCalendarPopup(True)
        self.setCellWidget(row,2,dte)

        # 职业下拉选择框
        cbw = QComboBox()
        professions = ["Doctor", "Lawyer", "Engineer", "Soldier", "Others"]
        cbw.addItems(professions)
        cbw.setCurrentText(profession if profession in professions else "Others")
        self.setCellWidget(row,3,cbw)

        # 薪资微调框
        sb = QSpinBox()
        sb.setRange(1000,1000000)
        sb.setValue(salary)#设置最开始显示的数字
        sb.setDisplayIntegerBase(10)#这个是显示数字的进制，默认是十进制。
        sb.setSuffix("元")#设置后辍
        sb.setPrefix("RMB: ")#设置前辍
        sb.setSingleStep(100)
        self.setCellWidget(row,4,sb)

# https://blog.csdn.net/taiyang1987912/article/details/47043937

if __name__ == '__main__':
    app = QApplication(sys.argv)
    TableWidget = TableWidget()
    TableWidget.show()
    app.exit(app.exec_())
