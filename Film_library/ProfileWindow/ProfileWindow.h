// Copyright 2025 Maslennikova Mary
#pragma once

#include "/git/Film_library/MainWindow/MainWindow.h"
#include "/git/Film_library/User/User.h"
#include "/git/Film_library/MyTVector/TVector.h"

namespace CppCLRWinFormsProject {
ref class MainWindow;
}

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
public ref class ProfileWindow : public System::Windows::Forms::Form {
private:
    MainWindow^ _mainWindow;
    User* _user;
public:
    ProfileWindow(User* user, MainWindow^ mainWindow) {
        InitializeComponent();
        this->_user = user;
        this->_mainWindow = mainWindow;
        ShowProfile();
    }

protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~ProfileWindow() {
        if (components)
        {
            delete components;
        }
    }

private: System::Windows::Forms::Button^ exit_btn;
private: System::Windows::Forms::ListBox^ favorites_box;
private: System::Windows::Forms::ListBox^ watched_box;


private: System::Windows::Forms::Label^ label1;
private: System::Windows::Forms::Label^ label2;
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
        this->exit_btn = (gcnew System::Windows::Forms::Button());
        this->favorites_box = (gcnew System::Windows::Forms::ListBox());
        this->watched_box = (gcnew System::Windows::Forms::ListBox());
        this->label1 = (gcnew System::Windows::Forms::Label());
        this->label2 = (gcnew System::Windows::Forms::Label());
        this->SuspendLayout();
        //
        // exit_btn
        //
        this->exit_btn->Font = (gcnew System::Drawing::Font
        (L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->exit_btn->Location = System::Drawing::Point(687, 22);
        this->exit_btn->Name = L"exit_btn";
        this->exit_btn->Size = System::Drawing::Size(117, 37);
        this->exit_btn->TabIndex = 1;
        this->exit_btn->Text = L"Exit";
        this->exit_btn->UseVisualStyleBackColor = true;
        this->exit_btn->Click += gcnew System::EventHandler(this,
            &ProfileWindow::exit_btn_Click);
        //
        // favorites_box
        //
        this->favorites_box->FormattingEnabled = true;
        this->favorites_box->Location = System::Drawing::Point(91, 174);
        this->favorites_box->Name = L"favorites_box";
        this->favorites_box->Size = System::Drawing::Size(262, 342);
        this->favorites_box->TabIndex = 2;
        //
        // watched_box
        //
        this->watched_box->FormattingEnabled = true;
        this->watched_box->Location = System::Drawing::Point(444, 174);
        this->watched_box->Name = L"watched_box";
        this->watched_box->Size = System::Drawing::Size(262, 342);
        this->watched_box->TabIndex = 3;
        //
        // label1
        //
        this->label1->AutoSize = true;
        this->label1->Font = (gcnew System::Drawing::Font(
            L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->label1->Location = System::Drawing::Point(180, 126);
        this->label1->Name = L"label1";
        this->label1->Size = System::Drawing::Size(95, 24);
        this->label1->TabIndex = 4;
        this->label1->Text = L"Favorites";
        //
        // label2
        //
        this->label2->AutoSize = true;
        this->label2->Font = (gcnew System::Drawing::Font
        (L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->label2->Location = System::Drawing::Point(528, 126);
        this->label2->Name = L"label2";
        this->label2->Size = System::Drawing::Size(92, 24);
        this->label2->TabIndex = 5;
        this->label2->Text = L"Watched";
        //
        // ProfileWindow
        //
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(816, 558);
        this->Controls->Add(this->label2);
        this->Controls->Add(this->label1);
        this->Controls->Add(this->watched_box);
        this->Controls->Add(this->favorites_box);
        this->Controls->Add(this->exit_btn);
        this->Name = L"ProfileWindow";
        this->Text = L"ProfileWindow";
        this->ResumeLayout(false);
        this->PerformLayout();
    }
#pragma endregion
public: void ShowProfile() {
    favorites_box->Items->Clear();
    watched_box->Items->Clear();

    favorites_box->Font = gcnew System::Drawing::Font("Arial", 14,
        System::Drawing::FontStyle::Regular);
    watched_box->Font = gcnew System::Drawing::Font("Arial", 14,
        System::Drawing::FontStyle::Regular);

    for (const Film* film : _user->get_favorites()) {
        favorites_box->Items->Add(gcnew String(film->get_film_name().c_str()));
    }

    for (const Film* film : _user->get_watched()) {
        watched_box->Items->Add(gcnew String(film->get_film_name().c_str()));
    }
}
private: System::Void exit_btn_Click(System::Object^ sender,
    System::EventArgs^ e) {
    this->Hide();
    Form^ form = this->Owner;
    form->Show();
}
};
}
