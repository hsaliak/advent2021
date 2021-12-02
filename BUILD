cc_library(
    name = "hello_lib",
    deps = ["@absl//absl/strings"],
    hdrs = ["hello_lib.h"],
    srcs = ["hello_lib.cc"],
    visibility = ["//visibility:public"],
    )

cc_binary(
    name = "hello_world",
    deps = [":hello_lib"],
    srcs = ["hello_world.cc"],
    )

cc_test(
    name = "hello_test",
    size = "small",
    srcs = ["hello_test.cc"],
    deps = [
        ":hello_lib",
        "@gtest//:gtest_main"],
    )
    
