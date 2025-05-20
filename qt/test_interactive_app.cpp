#include <QtTest/QtTest>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QApplication>

class TestInteractiveQtApp : public QObject
{
    Q_OBJECT

private slots:
    void testUpdateText();
    void testAlignmentChange();
    void testColorChange();
    void testResetButton();
};

void TestInteractiveQtApp::testUpdateText()
{
    QWidget window;
    window.setWindowTitle("Interactive Qt App");
    window.setFixedSize(400, 350);

    QVBoxLayout *layout = new QVBoxLayout(&window);

    QLabel *label = new QLabel("Hello! Enter text below:");
    layout->addWidget(label);

    QLineEdit *textInput = new QLineEdit();
    textInput->setPlaceholderText("Type something here...");
    layout->addWidget(textInput);

    QPushButton *updateButton = new QPushButton("Update Text");
    layout->addWidget(updateButton);

    QObject::connect(updateButton, &QPushButton::clicked, [&]() {
        QString inputText = textInput->text();
        if (!inputText.isEmpty()) {
            label->setText(inputText);
        } else {
            label->setText("Please enter some text!");
        }
    });

    // Simulate user input and click the button
    textInput->setText("Test Text");
    QTest::mouseClick(updateButton, Qt::LeftButton);

    // Verify label text is updated
    QCOMPARE(label->text(), QString("Test Text"));
}

void TestInteractiveQtApp::testAlignmentChange()
{
    QWidget window;
    window.setWindowTitle("Interactive Qt App");
    window.setFixedSize(400, 350);

    QVBoxLayout *layout = new QVBoxLayout(&window);

    QLabel *label = new QLabel("Hello! Enter text below:");
    layout->addWidget(label);

    QComboBox *alignmentBox = new QComboBox();
    alignmentBox->addItem("Align Center");
    alignmentBox->addItem("Align Left");
    alignmentBox->addItem("Align Right");
    layout->addWidget(alignmentBox);

    QObject::connect(alignmentBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index) {
        if (index == 0) {
            label->setAlignment(Qt::AlignCenter);
        } else if (index == 1) {
            label->setAlignment(Qt::AlignLeft);
        } else if (index == 2) {
            label->setAlignment(Qt::AlignRight);
        }
    });

    // Simulate selecting alignment
    alignmentBox->setCurrentIndex(1); // Align Left
    QCOMPARE(label->alignment(), Qt::AlignLeft);

    alignmentBox->setCurrentIndex(2); // Align Right
    QCOMPARE(label->alignment(), Qt::AlignRight);

    alignmentBox->setCurrentIndex(0); // Align Center
    QCOMPARE(label->alignment(), Qt::AlignCenter);
}

void TestInteractiveQtApp::testColorChange()
{
    QWidget window;
    window.setWindowTitle("Interactive Qt App");
    window.setFixedSize(400, 350);

    QVBoxLayout *layout = new QVBoxLayout(&window);

    QLabel *label = new QLabel("Hello! Enter text below:");
    layout->addWidget(label);

    QComboBox *colorBox = new QComboBox();
    colorBox->addItem("Black");
    colorBox->addItem("Red");
    colorBox->addItem("Blue");
    colorBox->addItem("Green");
    layout->addWidget(colorBox);

    QObject::connect(colorBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index) {
        if (index == 0) {
            label->setStyleSheet("color: black;");
        } else if (index == 1) {
            label->setStyleSheet("color: red;");
        } else if (index == 2) {
            label->setStyleSheet("color: blue;");
        } else if (index == 3) {
            label->setStyleSheet("color: green;");
        }
    });

    // Simulate color change
    colorBox->setCurrentIndex(1); // Red
    QCOMPARE(label->styleSheet(), QString("color: red;"));

    colorBox->setCurrentIndex(2); // Blue
    QCOMPARE(label->styleSheet(), QString("color: blue;"));

    colorBox->setCurrentIndex(0); // Black
    QCOMPARE(label->styleSheet(), QString("color: black;"));
}

void TestInteractiveQtApp::testResetButton()
{
    QWidget window;
    window.setWindowTitle("Interactive Qt App");
    window.setFixedSize(400, 350);

    QVBoxLayout *layout = new QVBoxLayout(&window);

    QLabel *label = new QLabel("Hello! Enter text below:");
    layout->addWidget(label);

    QLineEdit *textInput = new QLineEdit();
    textInput->setPlaceholderText("Type something here...");
    layout->addWidget(textInput);

    QPushButton *updateButton = new QPushButton("Update Text");
    layout->addWidget(updateButton);

    QPushButton *resetButton = new QPushButton("Reset");
    layout->addWidget(resetButton);

    QObject::connect(updateButton, &QPushButton::clicked, [&]() {
        QString inputText = textInput->text();
        if (!inputText.isEmpty()) {
            label->setText(inputText);
        } else {
            label->setText("Please enter some text!");
        }
    });

    QObject::connect(resetButton, &QPushButton::clicked, [&]() {
        textInput->clear();
        label->setText("Hello! Enter text below:");
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("color: black;");
    });

    // Simulate user input and click update
    textInput->setText("Test Reset");
    QTest::mouseClick(updateButton, Qt::LeftButton);
    QCOMPARE(label->text(), QString("Test Reset"));

    // Simulate reset button click
    QTest::mouseClick(resetButton, Qt::LeftButton);
    QCOMPARE(label->text(), QString("Hello! Enter text below:"));
    QCOMPARE(textInput->text(), QString(""));
}

QTEST_MAIN(TestInteractiveQtApp)
#include "test_interactive_app.moc"
