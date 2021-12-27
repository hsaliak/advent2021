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
    
cc_binary(
    name = "day1",
    deps = ["@absl//absl/flags:flag", 
            "@absl//absl/flags:parse", 
            "@absl//absl/status",
            "@glog//:glog"],
    srcs = ["day1.cc"],
    )
cc_binary(
    name = "day2",
    deps = ["@com_github_gflags_gflags//:gflags", 
            "@absl//absl/status",
            "@glog//:glog"],
    srcs = ["day2.cc"],
    )

cc_binary(
    name = "day3",
    deps = ["@com_github_gflags_gflags//:gflags", 
            "@absl//absl/status:statusor",
            "@glog//:glog"],
    srcs = ["day3.cc"],
    )

cc_binary(
    name = "day4",
    deps = ["@com_github_gflags_gflags//:gflags", 
            "@absl//absl/status:statusor",
            "@absl//absl/strings:strings",
            "@glog//:glog"],
    srcs = ["day4.cc"],
    )

cc_binary(
    name = "day5",
    deps = ["@com_github_gflags_gflags//:gflags", 
            "@absl//absl/status:statusor",
            "@absl//absl/strings:strings",
            "@absl//absl/container:flat_hash_map",
            "@glog//:glog"],
    srcs = ["day5.cc"],
    )

cc_binary(
    name = "day6",
    deps = ["@com_github_gflags_gflags//:gflags", 
            "@absl//absl/status:statusor",
            "@absl//absl/strings:strings",
            "@absl//absl/container:flat_hash_map",
            "@glog//:glog"],
    srcs = ["day6.cc"],
    )
cc_binary(
    name = "day7",
    deps = ["@com_github_gflags_gflags//:gflags", 
            "@absl//absl/status:statusor",
            "@absl//absl/strings:strings",
            "@absl//absl/hash:hash",
            "@absl//absl/container:flat_hash_map",
            "@glog//:glog"],
    srcs = ["day7.cc"],
    )
