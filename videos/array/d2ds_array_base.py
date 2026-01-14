import sys, os
from manim import *

# manim v0.18.1
# manim -pql videos/array/d2ds_array_base.py
# python videos/array/d2ds_array_base.py

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))

from libs import *

class D2DSArrayBase(Scene):
    def construct(self):

        contents = DContents([
            "0.基本概念",
            "1.内存布局",
            "2.应用示例",
        ]).arrange(DOWN, aligned_edge=LEFT).to_corner(UR)

        contents.scale(0.45)

        # 1. topic enter
        arr = self.start_scene()
        self.wait(1)

        # 2. base concept
        self.play(
            Create(contents),
            contents.anim_next_chapter()
        )
        arr_subscripts = self.base_concept(arr, contents)
        self.wait(1)

        # 3. memory layout
        self.play(contents.anim_next_chapter())
        self.memory_layout(arr, contents, arr_subscripts)
        self.wait(1)

        # 4. 应用场景
        self.play(contents.anim_next_chapter())
        self.apply_scene(contents)

    def apply_scene(self, contents):

        sub_contents_2_0 = Text("存储班级学生信息").scale(0.8).to_corner(UL)

        self.play(ReplacementTransform(contents[2].copy(), sub_contents_2_0))
        self.wait(1)

        code_dome1 = Code(code = """
int main() {
    Student s1 = {"鸣人", 10, "男"};
    Student s2 = {"佐助", 11, "男"};
    Student s3 = {"小樱", 10, "女"};
    // ...
    Student s30 = {"卡卡西", 30, "男"};

    send_data(s1, s2, s3, s4, ... s30);
    return 0;
}
        """, language="cpp", style="emacs").scale(0.7)
        self.play(Write(code_dome1))
        self.wait(1)

        code_dome2 = Code(code = """
int main() {
    Student students[30] = {
        {"鸣人", 10, "男"},
        {"佐助", 11, "男"},
        {"小樱", 10, "女"},
        // ...
        {"卡卡西", 30, "男"}
    };

    send_data(students, 30);
    return 0;
}
        """, language="cpp", style="emacs").scale(0.7).shift(DR)
        self.play(
            code_dome1.animate.shift(LEFT * 2 + UP * 1.5),
            Write(code_dome2)
        )
        self.wait(1)

    def memory_layout(self, arr, contents, arr_subscripts):

        sub_contents_1_0 = Text("连续内存存储").scale(0.8).to_corner(UL)
        sub_contents_1_1 = Text("地址计算").scale(0.8).to_corner(UL)

        self.play(ReplacementTransform(contents[1].copy(), sub_contents_1_0))
        self.wait(1)

        mem_loyout = DMemory(
            #[1, 2, 3, 4, 5, "...", 9],
            [".", ".", ".", ".", ".", "...", ".", "undefined"],
            addrs=["0x1000", "0x1004", "0x1008", "0x100d", "0x1010", "", "0x1020", "0x1024"]
        ).move_to(UP * 2 + RIGHT).scale(0.8)
        self.play(Create(mem_loyout))
        self.wait(1)

        for i in range(0, 5):
            self.play(ReplacementTransform(arr[i].text.copy(), mem_loyout.mem[i].text), run_time=0.5)
            if i == 4:
                mem_loyout.mem[i].set_value(65)
            else:
                mem_loyout.mem[i].set_value(i + 1)

        self.play(ReplacementTransform(arr[8].text.copy(), mem_loyout.mem[6].text), run_time=0.5)
        mem_loyout.mem[6].set_value(9)
        self.wait(1)

        self.play(
            ReplacementTransform(contents[1].copy(), sub_contents_1_1),
            FadeOut(sub_contents_1_0)
        )
        self.wait(1)

        self.play(
            mem_loyout.mem[4].animate.set_color(YELLOW),
            mem_loyout.mem[5].animate.set_opacity(0.3)
        )
        self.wait(1)

        addr_compute_formule = VGroup(
            Text("地址 = 基地址 + 偏移量"),
            VGroup(Text("addr = "), Text("base").scale(1.1), Text(" + ("), Text("index"), Text(" * "), Text("type_size"), Text(")")).arrange(RIGHT),
        ).arrange(DOWN, aligned_edge=LEFT).scale(0.5).to_edge(LEFT + UP * 3)

        self.play(Write(addr_compute_formule[0]))
        self.wait(1)
        self.play(ReplacementTransform(addr_compute_formule[0].copy(), addr_compute_formule[1]))
        self.wait(1)

        formule_tmp = VGroup(
            mem_loyout.addr_list[0].copy(),
            arr_subscripts[4].copy(),
        )
        self.play(
            formule_tmp[0].animate.move_to(addr_compute_formule[1][1]),
            FadeOut(addr_compute_formule[1][1])
        )
        self.wait(1)
        self.play(
            formule_tmp[1].animate.move_to(addr_compute_formule[1][3]),
            FadeOut(addr_compute_formule[1][3])
        )
        self.wait(1)
        self.play(Transform(addr_compute_formule[1][5], Text("sizeof(int)").scale(0.45).next_to(addr_compute_formule[1][5], ORIGIN)))
        self.wait(1)
        self.play(Transform(addr_compute_formule[1][5], Text("4").scale(0.5).next_to(addr_compute_formule[1][5], ORIGIN)))
        self.wait(1)

        self.play(DHighlight(mem_loyout.addr_list[4], scale_factor=1.2))

        addr_compute_formule[1][1] = formule_tmp[0]
        addr_compute_formule[1][3] = formule_tmp[1]
        self.play(
            FadeOut(VGroup(
                mem_loyout,
                addr_compute_formule,
                formule_tmp,
                sub_contents_1_1,
                arr,
                arr_subscripts
            ))
        )

    def base_concept(self, arr, contents):

        sub_contents_0_1 = Text("下标随机访问").scale(0.8).to_corner(UL)
        sub_contents_0_2 = Text("相同数据类型").scale(0.8).to_corner(UL)

        self.play(ReplacementTransform(contents[0].copy(), sub_contents_0_1))
        self.wait(1)

        arr_subscripts = arr.create_subscripts()
        self.play(Write(arr_subscripts))

        lua_arr_subscripts = arr.create_subscripts(start_index=1)
        lua_arr_subscripts.next_to(arr_subscripts, DOWN)
        lua_arr_subscripts.set_color(PURPLE)

        self.play(ReplacementTransform(arr_subscripts.copy(), lua_arr_subscripts))
        self.wait(1)

        self.play(FadeOut(lua_arr_subscripts))

        sourcecode = """arr[0]"""
        code = Code(code = sourcecode, language="cpp").move_to(LEFT * 2.5 + UP * 1.5)
        self.play(Write(code))
        self.wait(1)

        self.play(
            DHighlight(arr[0]),
            DHighlight(arr_subscripts[0]),
        )

        self.wait(1)

        self.play(Transform(code, Code(code = "arr[4]", language="cpp").next_to(code, ORIGIN)))
        self.play(
            DHighlight(arr[4]),
            DHighlight(arr_subscripts[4])
        )
        self.wait(1)

        self.play(Transform(code, Code(code = "arr[4] = 2025", language="cpp").next_to(code, ORIGIN)))
        self.wait(1)

        #new_value = DElement("2025").scale(0.5).next_to(arr[4], ORIGIN)
        self.play(Transform(arr[4], arr[4].copy().set_value("2025")))

        # 2. 同一数据类型
        self.play(
            ReplacementTransform(contents[0].copy(), sub_contents_0_2),
            FadeOut(sub_contents_0_1)
        )
        self.wait(1)

        sourcecode = """int arr[9] = {1, ... ,9};
arr[4] = 2025; // ok
arr[4] = "hello"; // error
arr[4] = 'A'; // ?"""

        self.play(Transform(code, Code(
            code = sourcecode, language="cpp", style="emacs"
        ).next_to(code, ORIGIN).scale(0.8)))
        self.wait(1)

        self.play(Transform(arr[4], arr[4].copy().set_value("hello").set_color(PURE_RED)))
        self.play(ApplyWave(arr[4]))
        self.wait(1)

        self.play(Transform(arr[4], arr[4].copy().set_value("65").set_color(YELLOW)))
        self.wait(1)

        self.play(FadeOut(code), FadeOut(sub_contents_0_2))

        return arr_subscripts

    def start_scene(self):
        text = Text("你学习的第一个数据结构是什么？")
        self.play(Write(text), run_time=1)
        self.wait(1)

        arr1 = DArray(["数", "组"])
        self.play(Transform(text, arr1))
        self.wait(1)

        arr2 = DArray([i for i in range(1, 10)]).scale(0.4).move_to(DOWN * 0.5)
        self.play(ReplacementTransform(text, arr2))
        self.wait(1)

        return arr2

if __name__ == "__main__":
    scene = D2DSArrayBase()
    scene.render()