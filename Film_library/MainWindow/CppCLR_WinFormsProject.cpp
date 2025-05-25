// Copyright 2025 Maslennikova Mary

#include "pch.h"

using namespace System;

// int main(array<System::String ^> ^args)
// {
//    return 0;
// }

#include "MainWindow.h"
#include "/git/Film_library/LoginWindow/LoginWindow.h"

using namespace System::Windows::Forms;

[STAThread]
int main() {
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);
  Application::Run(gcnew CppCLRWinFormsProject::MainWindow());
  return 0;
}
