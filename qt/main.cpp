#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create the main window
    QWidget window;
    window.setWindowTitle("Interactive Qt App");
    window.setFixedSize(400, 350);

    // Create a layout
    QVBoxLayout *layout = new QVBoxLayout(&window);

    // Create a label
    QLabel *label = new QLabel("Hello! Enter text below:");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    // Create a text input field
    QLineEdit *textInput = new QLineEdit();
    textInput->setPlaceholderText("Type something here...");
    layout->addWidget(textInput);

    // Create a button to update the label text
    QPushButton *updateButton = new QPushButton("Update Text");
    layout->addWidget(updateButton);

    // Connect the update button to the label
    QObject::connect(updateButton, &QPushButton::clicked, [&]() {
        QString inputText = textInput->text();
        if (!inputText.isEmpty()) {
            label->setText(inputText);
        } else {
            label->setText("Please enter some text!");
        }
    });

    // Create a dropdown (combo box) to change the label alignment
    QComboBox *alignmentBox = new QComboBox();
    alignmentBox->addItem("Align Center");
    alignmentBox->addItem("Align Left");
    alignmentBox->addItem("Align Right");
    layout->addWidget(alignmentBox);

    // Connect the dropdown to change the label alignment
    QObject::connect(alignmentBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index) {
        if (index == 0) { // Align Center
            label->setAlignment(Qt::AlignCenter);
        } else if (index == 1) { // Align Left
            label->setAlignment(Qt::AlignLeft);
        } else if (index == 2) { // Align Right
            label->setAlignment(Qt::AlignRight);
        }
    });

    // Create a dropdown (combo box) to change the label color
    QComboBox *colorBox = new QComboBox();
    colorBox->addItem("Black");
    colorBox->addItem("Red");
    colorBox->addItem("Blue");
    colorBox->addItem("Green");
    layout->addWidget(colorBox);

    // Connect the dropdown to change the label color
    QObject::connect(colorBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index) {
        if (index == 0) { // Black
            label->setStyleSheet("color: black;");
        } else if (index == 1) { // Red
            label->setStyleSheet("color: red;");
        } else if (index == 2) { // Blue
            label->setStyleSheet("color: blue;");
        } else if (index == 3) { // Green
            label->setStyleSheet("color: green;");
        }
    });

    // Create a reset button to clear the text and reset settings
    QPushButton *resetButton = new QPushButton("Reset");
    layout->addWidget(resetButton);
    QObject::connect(resetButton, &QPushButton::clicked, [&]() {
        textInput->clear();
        label->setText("Hello! Enter text below:");
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("color: black;"); // Reset to black color
    });

    // Show the window
    window.show();

    return app.exec();
}
