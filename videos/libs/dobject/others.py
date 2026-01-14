from manim import *

from .base import DElement

class DContents(VGroup):

    def __init__(self, contents, **kwargs):
        super().__init__(**kwargs)

        for i, e in enumerate(contents):
            self.add(Text(str(e)))

        self.arrange(DOWN)
        self.move_to(ORIGIN)

        self.select_rect = SurroundingRectangle(self[0])
        self.select_rect.set_opacity(0)
        self.add(self.select_rect)

        self.index = -1

    def anim_next_chapter(self):
        # return animation
        self.index = self.index + 1

        if self.index >= len(self) - 1:
            self.index = 0

        return Transform(self.select_rect, self._create_selector())

    def anim_prev_chapter(self):
        self.index = self.index - 1

        if self.index < 0:
            self.index = len(self) - 2

        return Transform(self.select_rect, self._create_selector())

    def _create_selector(self):
        s = SurroundingRectangle(self[self.index])
        s.set_color(YELLOW)
        s.set_opacity(0.15)
        return s

class DMemory(VGroup):

    def __init__(self, values, addrs=[], **kwargs):
        super().__init__(**kwargs)

        self.mem = VGroup()
        for value in values:
            element = DElement(value, width=1.5, height=0.5, color=PURPLE)
            element.box.set_fill(color=WHITE, opacity=0.2)
            self.mem.add(element)
        self.mem.arrange(DOWN, buff=0)

        addr_font_size = self.mem[0].text.font_size / 2
        self.addr_list = VGroup()
        for i, addr in enumerate(addrs):
            text = Text(str(addr), font_size=addr_font_size).set_color(PURE_RED)
            text.next_to(self.mem[i], LEFT)
            self.addr_list.add(text)

        self.add(self.mem, self.addr_list)
        self.move_to(ORIGIN)