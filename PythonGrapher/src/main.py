import re
import sys
import string
from sympy import *
from sympy.abc import x
from PyQt5 import QtCore
from PyQt5.QtWidgets import *
from numpy import arange, array
from matplotlib.figure import Figure
from function import sin, cos, tan, asin, acos, atan, exp, log, ln, pi, e
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas

func = 'x'

class Canvas(FigureCanvas):
	def __init__(self, parent=None, width=5, height=5, dpi=100):
		figure = Figure(figsize=(width, height), dpi=dpi)
		self.plt = figure.add_subplot(111)
		#self.plt.hold(False)
		
		FigureCanvas.__init__(self, figure)
		self.setParent(parent)

		FigureCanvas.setSizePolicy(self,
				QSizePolicy.Expanding,
				QSizePolicy.Expanding)
		FigureCanvas.updateGeometry(self)

class Graph(Canvas):	
   	def __init__(self, *args, **kwargs):
   		try:
   			global func
   			t = arange(-100, 100, 0.1)
		
   			f = lambdify(x, eval(func), modules = ['sympy'])
		
   			Canvas.__init__(self, *args, **kwargs)
	
   			self.plt.plot(t, f(t), label = func)
   			self.plt.axvline(x=0, color = 'k')
   			self.plt.axhline(y=0, color = 'k')
   			self.plt.grid(True)
   			self.draw()
   		except ValueError:
   			pass

class ApplicationWindow(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)
        self.setAttribute(QtCore.Qt.WA_DeleteOnClose)
        self.setWindowTitle("Calculator")

        self.main_widget = QWidget(self)

        self.grp = Graph(self.main_widget, width=5, height=5, dpi=100)
        
        self.equal = QPushButton("Equal", self)
        self.equal.clicked.connect(self.handleEqualButton)

        self.plot = QPushButton("Plot", self)
        self.plot.clicked.connect(self.handlePlotButton)

        self.answ = QTextEdit(self)
        self.expr = QTextEdit(self)

        self.main = QVBoxLayout(self.main_widget)

        self.main.addWidget(self.expr)
        self.main.addWidget(self.plot)
        self.main.addWidget(self.equal)
        self.main.addWidget(self.answ)

        self.answ.setReadOnly(True)

        self.main_widget.setFocus()
        self.setCentralWidget(self.main_widget)
        self.main.addWidget(self.grp)

        self.statusBar().showMessage(func)

    def handleEqualButton(self):
    	global func
    	func = self.expr.toPlainText()

    	self.answ.setText("%.10s" % str(eval(func)))
    	self.statusBar().showMessage(func)

    def handlePlotButton(self):
    	global func
    	func = self.expr.toPlainText()

    	self.main.removeWidget(self.grp)
    	self.grp.deleteLater()
    	self.grp = Graph(self.main_widget, width=5, height=5, dpi=100)
    	self.main.addWidget(self.grp)
    	self.statusBar().showMessage(func)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    aw = ApplicationWindow()
    aw.setWindowTitle("Calculator")
    aw.show()
    app.exec_()