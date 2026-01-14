from manim import *

from .base import DElement

class DArray(VGroup):

    def __init__(self, elements, **kwargs):
        super().__init__(**kwargs)
        for i, e in enumerate(elements):
            self.add(DElement(str(e)))

        self.arrange(RIGHT)
        self.move_to(ORIGIN)

    def create_subscripts(self, scale=0.6, start_index = 0, offset=DOWN * 1.5):
        sub_scripts = VGroup()

        for i in range(len(self)):
            sub_scripts.add(Text(str(i + start_index)).scale(scale).next_to(self[i], offset))

        sub_scripts.set_color(ORANGE)

        return sub_scripts

class DTwoDimArray(VGroup):

    def __init__(self, elements, **kwargs):
        super().__init__(**kwargs)
        self.elements = elements
        self.rows = len(elements)
        self.cols = len(elements[0])

        for i in range(self.rows):
            row = DArray(elements[i])
            row.move_to(UP * i)
            self.add(row)

        self.arrange(DOWN)
        self.move_to(ORIGIN)

    def create_subscripts(self, scale=0.6, start_index = 0, offset=1.5):
        sub_scripts = VGroup(VGroup(), VGroup())
        for i in range(self.rows):
            sub_scripts[0].add(Text(str(i + start_index)).scale(scale).next_to(self[i][0], offset * LEFT))
        sub_scripts[0].set_color(ORANGE)

        for i in range(self.cols):
            sub_scripts[1].add(Text(str(i + start_index)).scale(scale).next_to(self[0][i], offset * UP))
        sub_scripts[1].set_color(ORANGE)

        return sub_scripts