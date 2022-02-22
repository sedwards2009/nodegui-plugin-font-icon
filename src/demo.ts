import { FlexLayout, QFont, QFontDatabase, QPushButton, QLabel, QWidget, QMainWindow, QSize } from '@nodegui/nodegui';
import { createFontIcon } from './index';
import * as path from 'path';

// Load in our custom icon font
const extraicons = path.join(__dirname, "../resources/extraicons.ttf");
QFontDatabase.addApplicationFont(extraicons);

const win = new QMainWindow();
win.setWindowTitle('Font Icon Demo');

const centralWidget = new QWidget();
centralWidget.setObjectName('myroot');
const rootLayout = new FlexLayout();
centralWidget.setLayout(rootLayout);

const font = new QFont("extraicons", 10)

const label = new QLabel();
label.setText('Push buttons with font icons');
rootLayout.addWidget(label);

const button = new QPushButton();
const icon = createFontIcon(font, "\uEA09");  // Pocketknife icon
button.setIcon(icon);
button.setText('Font Icon');
rootLayout.addWidget(button);

const button2 = new QPushButton();
const icon2 = createFontIcon(font, "\uEA09");
button2.setIcon(icon2);
button2.setText('Font Icon Disabled');
button2.setEnabled(false);
rootLayout.addWidget(button2);

const button3 = new QPushButton();
const icon3 = createFontIcon(font, "\uEA09");
button3.setIcon(icon3);
button3.setText('Font Icon 32x32');
button3.setIconSize(new QSize(32, 32));
rootLayout.addWidget(button3);

const button4 = new QPushButton();
const icon4 = createFontIcon(font, "\uEA09");
button4.setIcon(icon4);
button4.setText('Font Icon 64x64');
button4.setIconSize(new QSize(64, 64));
rootLayout.addWidget(button4);

const buttonRotation90 = new QPushButton();
const iconRotation90 = createFontIcon(font, "\uEA09", { rotation: 90 });
buttonRotation90.setIcon(iconRotation90);
buttonRotation90.setText('Font Icon Rotation 90');
buttonRotation90.setIconSize(new QSize(64, 64));
rootLayout.addWidget(buttonRotation90);

const buttonRotation180 = new QPushButton();
const iconRotation180 = createFontIcon(font, "\uEA09", { rotation: 180 });
buttonRotation180.setIcon(iconRotation180);
buttonRotation180.setText('Font Icon Rotation 180');
buttonRotation180.setIconSize(new QSize(64, 64));
rootLayout.addWidget(buttonRotation180);

win.setCentralWidget(centralWidget);

win.show();

(global as any).win = win;
