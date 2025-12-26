include(FetchContent)

FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

FetchContent_Declare(
  ftxui_image_view
  GIT_REPOSITORY https://github.com/ljrrjl/ftxui-image-view
)
FetchContent_MakeAvailable(ftxui_image_view)

