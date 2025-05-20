/**
 * @jest-environment jsdom
 */

// Mock PIXI.Text class
class MockPixiText {
    constructor(initialText, style) {
      this.text = initialText;
      this.style = style;
      this.anchor = { set: jest.fn() };
      this.x = 0;
      this.y = 0;
    }
  }
  
  describe('PIXUI Controls with PIXI.Text mock', () => {
    let input, displayBtn, deleteBtn, textDisplay;
  
    beforeEach(() => {
      document.body.innerHTML = `
        <div id="controls">
          <input type="text" id="textInput" placeholder="Enter text to display" />
          <button id="displayButton">Display Text</button>
          <button id="deleteButton">Delete Text</button>
        </div>
      `;
  
      input = document.getElementById('textInput');
      displayBtn = document.getElementById('displayButton');
      deleteBtn = document.getElementById('deleteButton');
  
      // Create a mocked PIXI.Text instance (simulating the app's textDisplay)
      textDisplay = new MockPixiText('Welcome!', { fontFamily: 'Arial', fontSize: 28, fill: '#000000', align: 'center' });
  
      // Attach event handlers like the app
      displayBtn.addEventListener('click', () => {
        const inputText = input.value.trim();
        if (inputText) {
          textDisplay.text = inputText;
        } else {
          alert('Please enter some text to display!');
        }
      });
  
      deleteBtn.addEventListener('click', () => {
        textDisplay.text = ''; // Clear PIXI text object
        input.value = '';      // Clear input field as well
      });
    });
  
    // Test that the input field updates its value correctly and can be cleared
    test('input should update and clear', () => {
      input.value = 'Hello PIXI!';
      expect(input.value).toBe('Hello PIXI!');
      input.value = '';
      expect(input.value).toBe('');
    });
  
    // Test that clicking the display button with empty input triggers an alert
    test('display button triggers alert when input is empty', () => {
      const mockAlert = jest.spyOn(window, 'alert').mockImplementation(() => {});
      input.value = ''; // simulate empty input
      displayBtn.click();
      expect(mockAlert).toHaveBeenCalledWith('Please enter some text to display!');
      mockAlert.mockRestore();
    });
  
    // Test that clicking the display button updates the PIXI.Text object's text property with the input value
    test('display button updates PIXI text with input', () => {
      input.value = 'New Text';
      displayBtn.click();
      expect(textDisplay.text).toBe('New Text');
    });
  
    // Test that clicking the delete button clears both the PIXI text and the input field
    test('delete button clears PIXI text and input field', () => {
      input.value = 'Delete me';
      textDisplay.text = 'Some text';
      deleteBtn.click();
      expect(textDisplay.text).toBe('');
      expect(input.value).toBe('');
    });
  });
  