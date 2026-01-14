from manim import *

class DElement(VGroup):
    def __init__(self, text, width=2, height=2, max_font_size=48, color=BLUE, **kwargs):

        super().__init__(**kwargs)

        self.box = Rectangle(width=width, height=height, color=color)

        self.text = Text(str(text), font_size=max_font_size)
        
        # auto adjust font size
        self._auto_adjust_font_size()
        
        # align text and box
        self.add(self.box, self.text)
        self.text.move_to(self.box.get_center())

    def set_value(self, value):
        self.text.become(Text(str(value), font_size=self.text.font_size).next_to(self.box, ORIGIN))
        self._auto_adjust_font_size()
        return self
    
    def _auto_adjust_font_size(self):
        while self.text.width > self.box.get_width() * 0.8 or self.text.height > self.box.get_height() * 0.7:
            self.text.set_font_size(self.text.font_size - 2)