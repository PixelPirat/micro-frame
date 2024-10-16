const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const glfw = b.addStaticLibrary(.{
        .name = "glfw",
        .target = target,
        .optimize = optimize,
    });

    glfw.addIncludePath(b.path("libs/glfw/src"));
    glfw.addIncludePath(b.path("libs/glfw/include"));

    glfw.linkLibC();

    if (target.result.os.tag == .windows) {
        glfw.linkSystemLibrary("gdi32");

        const glfw_c_flags = .{"-D_GLFW_WIN32"};
        glfw.addCSourceFiles(.{
            .files = &glfw_base_sources,
            .flags = &glfw_c_flags,
        });
        glfw.addCSourceFiles(.{
            .files = &glfw_windows_sources,
            .flags = &glfw_c_flags,
        });
    } else {
        std.debug.print("Only Windows is supported!\n", .{});
        return;
    }

    b.installArtifact(glfw);

    const imgui = b.addStaticLibrary(.{
        .name = "imgui",
        .target = target,
        .optimize = optimize,
    });

    imgui.addIncludePath(b.path("libs/imgui"));
    imgui.addIncludePath(b.path("libs/imgui/backends"));
    imgui.addIncludePath(b.path("libs/glfw/include"));

    imgui.linkLibCpp();

    const imgui_c_flags = .{ "-std=c++11", "-Wall" };
    imgui.addCSourceFiles(.{
        .files = &imgui_sources,
        .flags = &imgui_c_flags,
    });

    b.installArtifact(imgui);

    const micro_frame = b.addExecutable(.{
        .name = "micro-frame",
        .target = target,
        .optimize = optimize,
    });

    micro_frame.addIncludePath(b.path("libs/glfw/include"));
    micro_frame.addIncludePath(b.path("libs/imgui"));
    micro_frame.addIncludePath(b.path("data"));
    micro_frame.addIncludePath(b.path("src/mdi"));

    const micro_frame_c_flags = .{ "-std=c++11", "-Wall" };
    micro_frame.addCSourceFiles(.{
        .files = &micro_frame_sources,
        .flags = &micro_frame_c_flags,
    });

    micro_frame.linkLibCpp();
    micro_frame.linkSystemLibrary("opengl32");
    micro_frame.linkLibrary(glfw);
    micro_frame.linkLibrary(imgui);

    b.installArtifact(micro_frame);

    const run_cmd = b.addRunArtifact(micro_frame);
    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}

const micro_frame_sources = .{ "src/main.cpp", "src/mdi/mdi.cpp" };

const glfw_base_sources = .{
    "libs/glfw/src/context.c",
    "libs/glfw/src/egl_context.c",
    "libs/glfw/src/init.c",
    "libs/glfw/src/input.c",
    "libs/glfw/src/monitor.c",
    "libs/glfw/src/null_init.c",
    "libs/glfw/src/null_joystick.c",
    "libs/glfw/src/null_monitor.c",
    "libs/glfw/src/null_window.c",
    "libs/glfw/src/osmesa_context.c",
    "libs/glfw/src/platform.c",
    "libs/glfw/src/vulkan.c",
    "libs/glfw/src/window.c",
};

const glfw_windows_sources = .{
    "libs/glfw/src/wgl_context.c",
    "libs/glfw/src/win32_init.c",
    "libs/glfw/src/win32_joystick.c",
    "libs/glfw/src/win32_module.c",
    "libs/glfw/src/win32_monitor.c",
    "libs/glfw/src/win32_thread.c",
    "libs/glfw/src/win32_time.c",
    "libs/glfw/src/win32_window.c",
};

const imgui_sources = .{
    "libs/imgui/imgui.cpp",
    "libs/imgui/imgui_demo.cpp",
    "libs/imgui/imgui_draw.cpp",
    "libs/imgui/imgui_tables.cpp",
    "libs/imgui/imgui_widgets.cpp",
    "libs/imgui/backends/imgui_impl_opengl3.cpp",
    "libs/imgui/backends/imgui_impl_glfw.cpp",
};
