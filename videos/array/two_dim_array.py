import sys, os
from manim import *

# manim v0.18.1
# manim -pql videos/array/two_dim_array.py
# python videos/array/two_dim_array.py

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))

from libs import *

class D2DSTwoDimArray(Scene):
    def construct(self):

        contents = DContents([
            "0.内存布局",
            "1.行/列优先存储",
            "2.性能/局部性原理",
        ]).arrange(DOWN, aligned_edge=LEFT).move_to(UR * 3 + RIGHT * 2)

        contents.scale(0.45)

        one_dim_arr =  DArray([i for i in range(1, 13)]).scale(0.3)
        one_dim_arr_title = Text("一维数组(arr1)").scale(0.5).next_to(one_dim_arr, UP)

        mem_loyout = DMemory(
            [i for i in range(1, 13)],
            ["0x0000", "0x0004", "0x0008", "0x000C", 
             "0x0010", "0x0014", "0x0018", "0x001C",
             "0x0020", "0x0024", "0x0028", "0x002C"],
        ).move_to(RIGHT * 3).scale(0.8)

        mem_loyout_title = Text("内存布局(R)").scale(0.5).next_to(mem_loyout, UP)

        self.play(Create(VGroup(one_dim_arr, one_dim_arr_title)))

        self.wait()

        self.play(
            ReplacementTransform(one_dim_arr.copy(), mem_loyout.mem),
            VGroup(one_dim_arr, one_dim_arr_title).animate.move_to(LEFT * 2),
        )

        two_dim_array = DTwoDimArray([
            [1, 2, 3],
            [4, 5, 6],
            [7, 8, 9],
            [10, 11, 12],
        ]).scale(0.3).move_to(one_dim_arr, ORIGIN).shift(LEFT)

        two_dim_array_title = Text("二维数组(arr2)").scale(0.5).next_to(two_dim_array, UP * 3).shift(LEFT * 0.25)

        self.play(
            ReplacementTransform(
                VGroup(one_dim_arr, one_dim_arr_title),
                VGroup(two_dim_array_title, two_dim_array),
            ),
        )

        arr_subscripts = two_dim_array.create_subscripts(scale=0.4, offset=1.2)

        self.play(
            Write(arr_subscripts),
        )

        self.wait()

        self.play(
            FadeIn(mem_loyout.addr_list),
            Create(mem_loyout_title)
        )

        #self.play(DHighlight(two_dim_array))

        for i in range(0, 4):
            self.play(
                DHighlight(two_dim_array[i]),
                DHighlight(VGroup(mem_loyout.mem[i * 3], mem_loyout.mem[i * 3 + 1], mem_loyout.mem[i * 3 + 2])),
                run_time=0.5,
            )

        # 1. one-dim / two-dim index compute

        code = Code(code = "arr2[1][1]", language="cpp", style="emacs")

        select_box = SurroundingRectangle(two_dim_array[1][1], color=YELLOW, buff=0.1)
        #select_box_1 = SurroundingRectangle(one_dim_arr[4], color=YELLOW, buff=0.1)
        select_box_r = SurroundingRectangle(mem_loyout.mem[4], color=YELLOW, buff=0.1)

        self.play(Write(code))
        self.play(DHighlight(select_box, scale_factor=1.2))

        self.wait()

        self.play(Transform(code, Code(code = "arr2[1][1]\narr1[1*3+1]", language="cpp", style="emacs").move_to(code)))
        #self.play(Transform(code, Code(code = "arr2[1][1]\narr1[4]", language="cpp", style="emacs").move_to(code)))

        self.play(ReplacementTransform(select_box.copy(), select_box_r))

        self.play(
            DHighlight(select_box_r, scale_factor=1.2),
            DHighlight(select_box, scale_factor=1.2),
        )

        self.wait()

        self.play(Transform(code, Code(code = "arr2[1][1]\narr1[4]\n// int (*)[3]\np = arr1", language="cpp", style="emacs").move_to(code)))
        self.wait()
        self.play(Transform(code, Code(code = "arr2[1][1]\narr1[4] // 5\n// int (*)[3]\np = arr1\np[1][1] // 5", language="cpp", style="emacs").move_to(code)))

        self.wait()

        # 2. row/column major
        self.play(
            FadeOut(code),
            FadeOut(VGroup(select_box, select_box_r)),
        )

        self.play(VGroup(mem_loyout, mem_loyout_title).animate.shift(RIGHT * 1.5))

        mem_loyout_col_major = DMemory(
            [1, 4, 7, 10,
             2, 5, 8, 11,
             3, 6, 9, 12],
            ["0x0000", "0x0004", "0x0008", "0x000C",
                "0x0010", "0x0014", "0x0018", "0x001C",
                "0x0020", "0x0024", "0x0028", "0x002C"],
        ).move_to(RIGHT * 2).scale(0.8)

        mem_loyout_col_major_title = Text("内存布局(C)").scale(0.5).next_to(mem_loyout_col_major, UP)

        self.play(Create(mem_loyout_col_major_title))

        for j in range(0, 3):
            mem_highlight = VGroup()
            arr_highlight = VGroup()
            for i in range(0, 4):
                mem_highlight.add(mem_loyout_col_major.mem[j * 4 + i])
                arr_highlight.add(two_dim_array[i][j])
                self.play(
                    ReplacementTransform(two_dim_array[i][j].copy(), mem_loyout_col_major.mem[j * 4 + i]),
                    FadeIn(mem_loyout_col_major.addr_list[j * 4 + i]),
                    run_time=0.2,
                )
            self.play(
                DHighlight(arr_highlight),
                DHighlight(mem_highlight),
                run_time=0.5
            )

        self.wait()

        self.play(DHighlight(select_box, scale_factor=1.2))

        select_box_r.move_to(mem_loyout.mem[4])
        select_box_c = SurroundingRectangle(mem_loyout_col_major.mem[5], color=YELLOW, buff=0.1)

        self.play(
            ReplacementTransform(select_box.copy(), select_box_r),
            ReplacementTransform(select_box.copy(), select_box_c),
        )

        self.wait()

        # 3. compute sum
        code_r = Code(code = """// 行优先遍历
for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
        sum += arr2[i][j];
    }
}""", language="cpp", style="emacs").shift(UP * 1.5)

        code_c = Code(code = """// 列优先遍历
for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
        sum += arr2[j][i];
    }
}""", language="cpp", style="emacs").shift(DOWN * 1.5)

        arr2_group = VGroup(two_dim_array, two_dim_array_title, arr_subscripts)
        mem_loyout_group = VGroup(
            mem_loyout, mem_loyout_title,
            mem_loyout_col_major, mem_loyout_col_major_title,
        )

        arr2_group_copy = arr2_group.copy()
        mem_layout_group_copy = mem_loyout_group.copy()

        arr2_group.add(select_box)
        mem_loyout_group.add(select_box_r, select_box_c)
        self.play(
            ReplacementTransform(arr2_group, code_r),
            ReplacementTransform(mem_loyout_group, code_c),
        )

        self.wait()

        setting_text = Code(code = """硬件信息
// Cache/内存块大小: 3个元素
// Cache命中: 0.1s
// Cache未命中: 1s""", language="cpp", style="emacs")

        self.play(ReplacementTransform(VGroup(code_r, code_c), setting_text))

        self.wait()

        self.play(setting_text.animate.scale(0.5).to_corner(UL))

        # 4. performance
        two_dim_array_copy = arr2_group_copy[0]
        mem_layout_r = VGroup(mem_layout_group_copy[0], mem_layout_group_copy[1])
        mem_layout_r.move_to(RIGHT * 3)

        self.play(
            FadeIn(arr2_group_copy),
            FadeIn(mem_layout_r),
        )

        cache = Rectangle(width=1.5, height=1.8, color=PURE_RED, fill_opacity=0.1)
        cache.set_stroke_color(GREEN)
        cache_title = Text("Cache").scale(0.5).next_to(cache, UP)

        cache = VGroup(cache, cache_title)

        self.play(Create(cache))

        select_box = SurroundingRectangle(two_dim_array_copy[0][0], color=YELLOW, buff=0.1)

        self.play(DHighlight(select_box, color = PURE_RED, scale_factor=1.2))

        self.wait()

        cache_line = VGroup(*[ mem_layout_r[0].mem[i].copy() for i in range(0, 3) ])
        self.play(Transform(cache_line, cache_line.copy().move_to(cache[0])))

        compute_time = Text("1s").scale(0.5).to_edge(UP)
        self.play(
            Write(compute_time),
            DHighlight(cache_line[0]),
        )

        self.play(select_box.animate.move_to(two_dim_array_copy[0][1]))
        self.play(
            DHighlight(cache_line[1]),
            Transform(compute_time, Text("1s + 0.1s").scale(0.5).to_edge(UP))
        )
        self.play(select_box.animate.move_to(two_dim_array_copy[0][2]))
        self.play(
            DHighlight(cache_line[2]),
            Transform(compute_time, Text("1s + 0.1s + 0.1s").scale(0.5).to_edge(UP))
        )
        self.play(select_box.animate.move_to(two_dim_array_copy[1][0]))

        self.play(DHighlight(select_box, color = PURE_RED, scale_factor=1.2))

        cache_line_new = VGroup(*[ mem_layout_r[0].mem[i].copy() for i in range(3, 6) ])
        self.play(
            FadeOut(cache_line),
            Transform(cache_line_new, cache_line_new.copy().move_to(cache[0])),
        )

        self.play(
            FadeOut(select_box),
            Transform(compute_time, Text("(1s + 0.1s + 0.1s) x 4").scale(0.5).to_edge(UP))
        )

        compute_time_r = Text("按行遍历: 4.8s").set_color(PURE_GREEN).scale(0.5).to_corner(UR)
        self.play(ReplacementTransform(compute_time, compute_time_r))
        mem_layout_r.add(compute_time)

        self.wait()
        """
        mem_layout_c = VGroup(mem_layout_group_copy[2], mem_layout_group_copy[3])
        mem_layout_c.move_to(RIGHT * 3)

        self.play(
            FadeIn(mem_layout_c),
            mem_layout_r.animate.shift(RIGHT * 2.5),
        )
        """
        # 5. column major
        select_box = SurroundingRectangle(two_dim_array_copy[0][0], color=YELLOW, buff=0.1)

        self.play(DHighlight(select_box, color = PURE_RED, scale_factor=1.2))

        self.wait()

        cache_line = cache_line_new
        cache_line_new = VGroup(*[ mem_layout_r[0].mem[i].copy() for i in range(0, 3) ])

        self.play(
            FadeOut(cache_line),
            Transform(cache_line_new, cache_line_new.copy().move_to(cache[0]))
        )

        compute_time = Text("1s").scale(0.5).to_edge(UP)
        self.play(
            DHighlight(cache_line_new[0]),
            Write(compute_time)
        )

        self.play(select_box.animate.move_to(two_dim_array_copy[1][0]))

        self.play(DHighlight(select_box, color = PURE_RED, scale_factor=1.2))
        cache_line = cache_line_new
        cache_line_new = VGroup(*[ mem_layout_r[0].mem[i].copy() for i in range(3, 6) ])
        self.play(
            FadeOut(cache_line),
            Transform(cache_line_new, cache_line_new.copy().move_to(cache[0])),
        )

        self.play(
            DHighlight(cache_line_new[0]),
            Transform(compute_time, Text("1s + 1s").scale(0.5).to_edge(UP))
        )

        self.wait()

        compute_time_c = Text("按列遍历: 12s").set_color(ORANGE).scale(0.5).to_edge(UP)
        self.play(
            FadeOut(select_box),
            ReplacementTransform(compute_time, compute_time_c)
        )

        self.play(compute_time_c.animate.next_to(compute_time_r, DOWN * 0.5))

        self.wait()

if __name__ == "__main__":
    scene = D2DSTwoDimArray()
    scene.render()