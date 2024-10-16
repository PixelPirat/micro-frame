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

        //glfw.linkSystemLibrary("user32");
        //glfw.linkSystemLibrary("shell32");

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

    const exe = b.addExecutable(.{
        .name = "micro-frame",
        .target = target,
        .optimize = optimize,
    });

    exe.addIncludePath(b.path("libs/glfw/include"));

    const exe_c_flags = .{ "-std=c99", "-Wall" };
    exe.addCSourceFiles(.{
        .files = &micro_frame_sources,
        .flags = &exe_c_flags,
    });

    exe.linkLibC();
    exe.linkSystemLibrary("opengl32");
    exe.linkLibrary(glfw);

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}

const micro_frame_sources = .{"src/main.c"};

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
