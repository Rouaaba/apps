package com.skyguide.javaSwing;

import javax.swing.*;
import java.awt.*;

public class InteractiveSwingApp {
    private JFrame frame;
    private JTextField textField;
    private JButton displayButton;
    private JLabel displayedText;
    private JComboBox<String> colorComboBox;

    public InteractiveSwingApp() {
        frame = new JFrame("Interactive Swing App");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 400);
        frame.setLayout(new BorderLayout());

        JPanel controlPanel = new JPanel();
        controlPanel.setLayout(new GridLayout(4, 1, 10, 10)); // 4 rows (fixing previous 3,1)

        JLabel instructionLabel = new JLabel("Use the controls below to interact:");
        instructionLabel.setHorizontalAlignment(SwingConstants.CENTER);

        textField = new JTextField();
        textField.setName("textField");
        textField.setBorder(BorderFactory.createTitledBorder("Enter text here"));

        displayButton = new JButton("Display Text");
        displayButton.setName("displayButton");

        displayedText = new JLabel("", SwingConstants.CENTER);
        displayedText.setName("displayedText");  // <-- add this!


        displayButton.addActionListener(e -> {
            String text = textField.getText();
            if (!text.isEmpty()) {
                displayedText.setText("<html><strong>" + text + "</strong></html>");
            } else {
                displayedText.setText("Please enter something!");
            }
        });

        colorComboBox = new JComboBox<>(new String[]{"Black", "Red", "Blue", "Green"});
        colorComboBox.setName("colorComboBox");
        colorComboBox.setBorder(BorderFactory.createTitledBorder("Select text color"));
        colorComboBox.addActionListener(e -> {
            String selectedColor = (String) colorComboBox.getSelectedItem();
            switch (selectedColor) {
                case "Red":
                    displayedText.setForeground(Color.RED);
                    break;
                case "Blue":
                    displayedText.setForeground(Color.BLUE);
                    break;
                case "Green":
                    displayedText.setForeground(Color.GREEN);
                    break;
                default:
                    displayedText.setForeground(Color.BLACK);
                    break;
            }          
            
        });

        controlPanel.add(instructionLabel);
        controlPanel.add(textField);
        controlPanel.add(displayButton);
        controlPanel.add(colorComboBox);

        frame.add(controlPanel, BorderLayout.NORTH);
        frame.add(displayedText, BorderLayout.CENTER);
    }

    public JFrame getFrame() {
        return frame;
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            InteractiveSwingApp app = new InteractiveSwingApp();
            app.getFrame().setVisible(true);
        });
    }
}
