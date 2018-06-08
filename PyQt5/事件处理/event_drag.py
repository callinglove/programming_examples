import sys
from PyQt5.QtWidgets import (QPushButton, QWidget, QLineEdit, QApplication)

# https://www.cnblogs.com/findumars/p/5599422.html

class Button(QPushButton):
    def __init__(self, title, parent):
        super().__init__(title, parent)
        self.setAcceptDrops(True)

    def dragEnterEvent(self, e):
        # print(e.mimeData().text())
        # print(e.mimeData().Urls())
        if e.mimeData().hasFormat("text/plain"):
            e.accept()
        else:
            e.ignore()

    def dropEvent(self, e):
        self.setText(e.mimeData().text())

class LineEdit(QLineEdit):
    def __init__(self, title, parent):
        super().__init__(title, parent)
        self.setAcceptDrops(True)
        self.setDragEnabled(True)

    def dragEnterEvent(self, e):
        print(e.mimeData().formats())
        if e.mimeData().hasUrls():
            e.acceptProposedAction()

    def dropEvent(self, e):
        urls = e.mimeData().urls()
        if len(urls) == 0:
            return

        fileName = urls[0].toLocalFile()
        self.setText(fileName)


class Example(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        edit = LineEdit("", self)

        edit.move(30, 65)

        button = Button("Button", self)
        button.move(190, 65)

        self.setWindowTitle("Simple drag & drop")
        self.setGeometry(300, 300, 300, 150)
        self.show()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
