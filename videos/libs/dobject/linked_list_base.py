from manim import *

class DNode(VGroup):
    def __init__(self, value, **kwargs):
        super().__init__(**kwargs)
        self.rect = Rectangle(width = 1, height = 1)
        self.text = Text(str(value))
        self.add(self.rect, self.text)
        self.scale = 1

    def left_pos(self):
        return self.rect.get_center() - [self.rect.get_width() / 2, 0, 0]

    def right_pos(self):
        return self.rect.get_center() + [self.rect.get_width() / 2, 0, 0]

    def set_scale(self, scale):
        self.scale = scale
        self.rect.set_width(1 * scale)
        self.rect.set_height(1 * scale)
        self.text.scale(scale)
        return self

class DNodeLink(VGroup):
    def __init__(self, node1, node2, **kwargs):
        super().__init__(**kwargs)
        self.node1 = node1
        self.node2 = node2

        if node1.get_center()[0] < node2.get_center()[0]:
            self.start = node1.right_pos() + 0.1 * UP
            self.end = node2.left_pos() + 0.1 * UP
        else:
            self.start = node1.left_pos() + 0.1 * DOWN
            self.end = node2.right_pos() + 0.1 * DOWN

        self.arrow = Arrow(
            self.start , self.end,
            max_stroke_width_to_length_ratio = 2,
            max_tip_length_to_length_ratio = 0.125
        )
        self.add(self.arrow)

    def get_arrow(self):
        return self.arrow

if __name__ == "__main__":
    scene = D2DSLogo()
    scene.render()