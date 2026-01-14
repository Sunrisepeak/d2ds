from manim import *
from libs import *

# manim -pql videos/d2ds_logo.py
# python videos/d2ds_logo.py

class D2DSLogo(Scene):
    def construct(self):
        node_d = DNode("D").move_to(LEFT * 2).set_scale(0.8)
        node_2 = DNode("2").move_to(UP * 1 + LEFT * 0.5).set_scale(0.8).set_color(PURE_RED)
        node_data = DNode("D").move_to(RIGHT).set_scale(0.8)
        node_s = DNode("S").move_to(RIGHT * 2).set_scale(0.8)

        self.add(node_d)
        #self.add(NumberPlane())

        link_d_to_data = DNodeLink(node_d, node_data)
        link_data_to_d = DNodeLink(node_data, node_d)
        link_d_to_data.set_color(PURE_GREEN).scale(0.7)
        link_data_to_d.set_color(ORANGE).scale(0.7)

        node_d_copy1 = node_d.copy()
        node_d_copy2 = node_d.copy()

        self.play(
            ReplacementTransform(node_d_copy1, node_s),
            ReplacementTransform(node_d_copy2, node_data),
            FadeIn(VGroup(link_d_to_data, link_data_to_d))
        )

        link_2_to_d = DNodeLink(node_2, node_d).set_color(ORANGE)
        link_2_to_data = DNodeLink(node_2, node_data).set_color(PURE_GREEN)

        self.add(node_2)
        self.play(
            Create(link_2_to_d),
            Create(link_2_to_data),
        )

        link_data_to_2 = DNodeLink(node_data, node_2).set_color(ORANGE)
        link_d_to_2 = DNodeLink(node_d, node_2).set_color(PURE_GREEN)

        self.play(
            ReplacementTransform(link_d_to_data, link_d_to_2),
            ReplacementTransform(link_data_to_d, link_data_to_2),
        )

        # fadeout all
        self.play(
            FadeOut(VGroup(node_d, node_2, node_data, node_s)),
            FadeOut(VGroup(
                link_2_to_d,
                link_2_to_data,
                link_data_to_2,
                link_d_to_2
            ))
        )

if __name__ == "__main__":
    scene = D2DSLogo()
    scene.render()