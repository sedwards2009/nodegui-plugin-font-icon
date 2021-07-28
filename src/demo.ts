import { FlexLayout, QFont, QPushButton, QLabel, QWidget, QMainWindow } from '@nodegui/nodegui';
import { createIcon } from './index';

const win = new QMainWindow();
win.setWindowTitle('Font Icon Demo');

const centralWidget = new QWidget();
centralWidget.setObjectName('myroot');
const rootLayout = new FlexLayout();
centralWidget.setLayout(rootLayout);

const font = new QFont("serif", 10)

const label = new QPushButton();
const icon = createIcon(font, "A");
label.setIcon(icon);
label.setText('<- Font Icon');
rootLayout.addWidget(label);


win.setCentralWidget(centralWidget);

win.show();



(global as any).win = win;