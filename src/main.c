#include "ui/mainwindow/mainwindow.h"

int main() {
  MainWindow app = {0};

  if (!main_window_init(&app, "Vane", 800, 600)) {
    return 1;
  }

  main_window_run(&app);
  main_window_destroy(&app);

  return 0;
}
