package com.skyguide.javaSwing;

import static org.assertj.swing.finder.WindowFinder.findFrame;
import static org.assertj.core.api.Assertions.assertThat;

import java.awt.Color;

import javax.swing.JLabel;
import javax.swing.SwingUtilities;

import org.assertj.swing.core.BasicRobot;
import org.assertj.swing.fixture.FrameFixture;
import org.assertj.swing.fixture.JButtonFixture;
import org.assertj.swing.fixture.JComboBoxFixture;
import org.assertj.swing.fixture.JLabelFixture;
import org.assertj.swing.fixture.JTextComponentFixture;
import org.assertj.swing.core.matcher.JButtonMatcher;
import org.assertj.swing.edt.GuiActionRunner;
import org.junit.jupiter.api.*;

public class InteractiveSwingAppTest {

    private FrameFixture window;
    private org.assertj.swing.core.Robot robot;

    @BeforeEach
    public void setUp() {
        robot = BasicRobot.robotWithNewAwtHierarchy();

        InteractiveSwingApp app = GuiActionRunner.execute(() -> new InteractiveSwingApp());
        window = new FrameFixture(robot, app.getFrame());
        window.show();  // important: makes the frame visible
    }

    @AfterEach
    public void tearDown() {
        window.cleanUp();
        robot.cleanUp();
    }

    @Test
    @DisplayName("Test entering text and displaying it on label")
    public void testDisplayText() {
        JTextComponentFixture textField = window.textBox("textField");
        JButtonFixture displayButton = window.button(JButtonMatcher.withName("displayButton"));
        JLabelFixture displayedLabel = window.label("displayedText");

        textField.setText("Hello Swing!");
        displayButton.click();
        
        assertThat(displayedLabel.text()).contains("Hello Swing!");
        assertThat(displayedLabel.text()).contains("<strong>");
        
    }

    @Test
    @DisplayName("Test display message when text input is empty")
    public void testEmptyInputMessage() {
        JTextComponentFixture textField = window.textBox("textField");
        JButtonFixture displayButton = window.button(JButtonMatcher.withName("displayButton"));
        JLabelFixture displayedLabel = window.label("displayedText");

        textField.setText("");
        displayButton.click();

        assertThat(displayedLabel.text()).isEqualTo("Please enter something!");
    }

    @Test
    @DisplayName("Test changing displayed text color")
    public void testChangeTextColor() {
        JTextComponentFixture textField = window.textBox("textField");
        JButtonFixture displayButton = window.button(JButtonMatcher.withName("displayButton"));
        JComboBoxFixture colorComboBox = window.comboBox("colorComboBox");
        JLabelFixture displayedLabel = window.label("displayedText");

        textField.enterText("Color Test");
        displayButton.click();

        colorComboBox.selectItem("Red");
        assertThat(displayedLabel.foreground().target()).isEqualTo(Color.RED);

        colorComboBox.selectItem("Blue");
        assertThat(displayedLabel.foreground().target()).isEqualTo(Color.BLUE);

        colorComboBox.selectItem("Green");
        assertThat(displayedLabel.foreground().target()).isEqualTo(Color.GREEN);

        colorComboBox.selectItem("Black");
        assertThat(displayedLabel.foreground().target()).isEqualTo(Color.BLACK);
    }
}
