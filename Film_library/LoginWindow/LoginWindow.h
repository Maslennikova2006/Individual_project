#pragma once
// Copyright 2025 Maslennikova Mary

#include <msclr/marshal_cppstd.h>
#include <fstream>
#include <string>

#include "/git/Film_library/MyTVector/TVector.h"
#include "/git/Film_library/User/User.h"
#include "/git/Film_library/MainWindow/MainWindow.h"


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
public ref class LoginWindow : public System::Windows::Forms::Form {
private:
    TVector<User>* users;
public:
    LoginWindow(void) {
        InitializeComponent();
        users = new TVector<User>();
        LoadUsers();
    }

protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~LoginWindow() {
        if (components) {
            delete components;
            delete users;
        }
    }
private: System::Windows::Forms::Button^ login_btn;
private: System::Windows::Forms::Button^ register_btn;
private: System::Windows::Forms::Label^ label1;
private: System::Windows::Forms::Label^ label2;
private: System::Windows::Forms::TextBox^ login_txt;
private: System::Windows::Forms::TextBox^ password_txt;
private: System::Windows::Forms::Label^ label3;
protected:
protected:
private:
    /// <summary>
    ///  Required designer variable.
    /// </summary>
    System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
    /// <summary>
    ///  Required method for Designer support - do not modify
    ///  the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void) {
        this->login_btn = (gcnew System::Windows::Forms::Button());
        this->register_btn = (gcnew System::Windows::Forms::Button());
        this->label1 = (gcnew System::Windows::Forms::Label());
        this->label2 = (gcnew System::Windows::Forms::Label());
        this->login_txt = (gcnew System::Windows::Forms::TextBox());
        this->password_txt = (gcnew System::Windows::Forms::TextBox());
        this->label3 = (gcnew System::Windows::Forms::Label());
        this->SuspendLayout();
        //
        //  login_btn
        //
        this->login_btn->Font = (gcnew System::Drawing::Font
        (L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->login_btn->Location = System::Drawing::Point(204, 399);
        this->login_btn->Name = L"login_btn";
        this->login_btn->Size = System::Drawing::Size(151, 45);
        this->login_btn->TabIndex = 0;
        this->login_btn->Text = L"Log in";
        this->login_btn->UseVisualStyleBackColor = true;
        this->login_btn->Click += gcnew System::
            EventHandler(this, &LoginWindow::login_btn_Click);
        //
        //  register_btn
        //
        this->register_btn->Font = (gcnew System::Drawing::Font
        (L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->register_btn->Location = System::Drawing::Point(405, 399);
        this->register_btn->Name = L"register_btn";
        this->register_btn->Size = System::Drawing::Size(151, 45);
        this->register_btn->TabIndex = 1;
        this->register_btn->Text = L"Register";
        this->register_btn->UseVisualStyleBackColor = true;
        this->register_btn->Click += gcnew System::
            EventHandler(this, &LoginWindow::register_btn_Click);
        //
        //  label1
        //
        this->label1->AutoSize = true;
        this->label1->Font = (gcnew System::Drawing::Font
        (L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->label1->Location = System::Drawing::Point(200, 231);
        this->label1->Name = L"label1";
        this->label1->Size = System::Drawing::Size(97, 24);
        this->label1->TabIndex = 2;
        this->label1->Text = L"Username";
        //
        //  label2
        //
        this->label2->AutoSize = true;
        this->label2->Font = (gcnew System::Drawing::Font
        (L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->label2->Location = System::Drawing::Point(200, 310);
        this->label2->Name = L"label2";
        this->label2->Size = System::Drawing::Size(92, 24);
        this->label2->TabIndex = 3;
        this->label2->Text = L"Password";
        //
        //  login_txt
        //
        this->login_txt->Font = (gcnew System::Drawing::Font
        (L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->login_txt->Location = System::Drawing::Point(314, 229);
        this->login_txt->Name = L"login_txt";
        this->login_txt->Size = System::Drawing::Size(241, 29);
        this->login_txt->TabIndex = 4;
        //
        //  password_txt
        //
        this->password_txt->Font = (gcnew System::Drawing::Font
        (L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->password_txt->Location = System::Drawing::Point(314, 307);
        this->password_txt->Name = L"password_txt";
        this->password_txt->Size = System::Drawing::Size(241, 29);
        this->password_txt->TabIndex = 5;
        //
        //  label3
        //
        this->label3->AutoSize = true;
        this->label3->Font = (gcnew System::Drawing::Font
        (L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->label3->Location = System::Drawing::Point(278, 159);
        this->label3->Name = L"label3";
        this->label3->Size = System::Drawing::Size(225, 33);
        this->label3->TabIndex = 6;
        this->label3->Text = L"FILM LIBRARY";
        //
        //  Form1
        //
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(768, 602);
        this->Controls->Add(this->label3);
        this->Controls->Add(this->password_txt);
        this->Controls->Add(this->login_txt);
        this->Controls->Add(this->label2);
        this->Controls->Add(this->label1);
        this->Controls->Add(this->register_btn);
        this->Controls->Add(this->login_btn);
        this->Name = L"LoginWindow";
        this->Text = L"LoginWindow";
        this->ResumeLayout(false);
        this->PerformLayout();
    }
#pragma endregion
public: void LoadUsers() {
    std::ifstream file("C:\\git\\Film_library\\users.txt");
    if (!file.is_open()) {
        System::Windows::Forms::MessageBox::Show(
            "The file users.txt not found!", "Error",
            System::Windows::Forms::MessageBoxButtons::OK,
            System::Windows::Forms::MessageBoxIcon::Error);
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t delimiter_pos = line.find(' ');
        std::string login = line.substr(0, delimiter_pos);
        std::string password = line.substr(delimiter_pos + 1);
        users->push_back(User(login, password));
    }
    file.close();
}
private: System::Void login_btn_Click
       (System::Object^ sender, System::EventArgs^ e) {
    std::string login = msclr::interop::
        marshal_as<std::string>(login_txt->Text);
    std::string password = msclr::interop::
        marshal_as<std::string>(password_txt->Text);
    if (login == "" || password == "") {
        System::Windows::Forms::MessageBox::Show(
            "Enter your username and password!", "Error",
            System::Windows::Forms::MessageBoxButtons::OK,
            System::Windows::Forms::MessageBoxIcon::Error);
        return;
    }

    try {
        User temporary_user(login, password);
        bool found = false;
        for (size_t i = 0; i < users->size(); i++) {
            if (users->at(i) == temporary_user) {
                found = true;
                break;
            }
        }
        if (found) {
            System::Windows::Forms::MessageBox::Show(
                "The login was completed successfully!", "Information",
                System::Windows::Forms::MessageBoxButtons::OK,
                System::Windows::Forms::MessageBoxIcon::Information);
            this->Hide();
            MainWindow^ window = gcnew MainWindow();
            window->ShowDialog(this);
        } else {
            System::Windows::Forms::MessageBox::Show(
                "The user is not registered!", "Error",
                System::Windows::Forms::MessageBoxButtons::OK,
                System::Windows::Forms::MessageBoxIcon::Error);
        }
    }
    catch (const std::exception& ex) {
        MessageBox::Show(gcnew System::String(ex.what()), "Error",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}
private: System::Void register_btn_Click
       (System::Object^ sender, System::EventArgs^ e) {
    std::string login = msclr::interop::
        marshal_as<std::string>(login_txt->Text);
    std::string password = msclr::interop::
        marshal_as<std::string>(password_txt->Text);

    if (login == "" || password == "") {
        System::Windows::Forms::MessageBox::Show(
            "Enter your username and password!", "Error",
            System::Windows::Forms::MessageBoxButtons::OK,
            System::Windows::Forms::MessageBoxIcon::Error);
        return;
    }
    try {
        User temporary_user(login, password);
        bool found = false;
        for (size_t i = 0; i < users->size(); i++) {
            if ((*users)[i].get_login() == login) {
                found = true;
                break;
            }
        }
        if (found) {
            System::Windows::Forms::MessageBox::Show(
                "Username already exists!", "Information",
                System::Windows::Forms::MessageBoxButtons::OK,
                System::Windows::Forms::MessageBoxIcon::Information);
            this->Hide();
            MainWindow^ window = gcnew MainWindow();
            window->Show(this);
        }
        else {
            std::ofstream outFile("C:\\git\\Film_library\\users.txt", std::ios::app);
            if (!outFile.is_open()) {
                MessageBox::Show("Cannot open users file!", "Error",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            outFile << std::endl << login << " " << password;
            outFile.close();

            MessageBox::Show("Registration successful!", "Information",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            this->Hide();
            MainWindow^ window = gcnew MainWindow();
            window->ShowDialog(this);
        }
    }
    catch (const std::exception& ex) {
        MessageBox::Show(gcnew System::String(ex.what()), "Error",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}
};
}  //  namespace CppCLRWinFormsProject
