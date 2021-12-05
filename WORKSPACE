load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "gtest",    url="https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip",
    sha256= "353571c2440176ded91c2de6d6cd88ddd41401d14692ec1f99e35d013feda55a",
    strip_prefix = "googletest-release-1.11.0",
)

http_archive(
  name = "absl",
  urls = ["https://github.com/abseil/abseil-cpp/archive/refs/heads/lts_2021_11_02.zip"],
    sha256= "964a76c6e77bfc928765b2efa36472ae3dfc69c727d616d19d143bc5d658230a",
    strip_prefix = "abseil-cpp-lts_2021_11_02/",
)


http_archive(
    name = "com_github_google_benchmark",
    urls = ["https://github.com/google/benchmark/archive/bf585a2789e30585b4e3ce6baf11ef2750b54677.zip"],
    strip_prefix = "benchmark-bf585a2789e30585b4e3ce6baf11ef2750b54677",
    sha256 = "2a778d821997df7d8646c9c59b8edb9a573a6e04c534c01892a40aa524a7b68c",
)
http_archive(
    name = "com_github_gflags_gflags",
    sha256 = "34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf",
    strip_prefix = "gflags-2.2.2",
    urls = ["https://github.com/gflags/gflags/archive/v2.2.2.tar.gz"],
)

http_archive(
    name = "glog",
    sha256 = "21bc744fb7f2fa701ee8db339ded7dce4f975d0d55837a97be7d46e8382dea5a",
    strip_prefix = "glog-0.5.0",
    urls = ["https://github.com/google/glog/archive/v0.5.0.zip"],
)
