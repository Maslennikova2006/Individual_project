// Copyright 2025 Maslennikova Mary

#pragma once

#include <fstream>
#include <iostream>

#include "/git/Film_library/Film/Film.h"
#include "/git/Film_library/Film_library/Film_library.h"
#include "/git/Film_library/MyTVector/TVector.h"

namespace CppCLRWinFormsProject {
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Summary for Form1
/// </summary>
public ref class MainWindow : public System::Windows::Forms::Form {
public:
    MainWindow(void) {
        InitializeComponent();
        //
        // TODO(Maslennikova Mary): Add the constructor code here
        //
        this->AutoScroll = true;
    }

protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~MainWindow() {
        if (components) {
            delete components;
        }
    }

protected:
private:
    /// <summary>
    /// Required designer variable.
    /// </summary>
    System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void) {
        this->SuspendLayout();
        //
        // MainWindow
        //
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(984, 561);
        this->Name = L"MainWindow";
        this->Text = L"MainWindow";
        this->Load += gcnew System::EventHandler
        (this, &MainWindow::MainWindow_Load);
        this->ResumeLayout(false);
    }
#pragma endregion
private: System::Void MainWindow_Load
       (System::Object^ sender, System::EventArgs^ e) {
}
};
}  // namespace CppCLRWinFormsProject
