// Copyright 2025 Maslennikova Mary

#pragma once
#include <msclr/marshal_cppstd.h>

#include <fstream>
#include <iostream>
#include <string>

#include "/git/Film_library/Actor/Actor.h"
#include "/git/Film_library/Creator/Creator.h"
#include "/git/Film_library/Date_of_birth/Date.h"
#include "/git/Film_library/Feedback/Feedback.h"
#include "/git/Film_library/Film/Film.h"
#include "/git/Film_library/Film_director/Director.h"
#include "/git/Film_library/Film_library/Film_library.h"
#include "/git/Film_library/FIO/FIO.h"
#include "/git/Film_library/User/User.h"
#include "/git/Film_library/MyTVector/TVector.h"
#include "/git/Film_library/ProfileWindow/ProfileWindow.h"

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
private:
       User* _user;
       FilmLibrary* filmLibrary;
private: System::Windows::Forms::Button^ profile_btn;
public:
    MainWindow(FilmLibrary* film_library, User* user) {
        InitializeComponent();
        this->filmLibrary = film_library;
        this->_user = user;
        ShowFilms();
    }
    MainWindow(User* user) {
        InitializeComponent();
        this->_user = user;
        ShowFilms();
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
private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanelFilms;
protected:
private: System::Windows::Forms::Label^ label1;
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
        this->flowLayoutPanelFilms = (gcnew System::Windows::Forms::FlowLayoutPanel());
        this->label1 = (gcnew System::Windows::Forms::Label());
        this->profile_btn = (gcnew System::Windows::Forms::Button());
        this->SuspendLayout();
        // 
        // flowLayoutPanelFilms
        // 
        this->flowLayoutPanelFilms->AutoScroll = true;
        this->flowLayoutPanelFilms->Location = System::Drawing::Point(0, 162);
        this->flowLayoutPanelFilms->Name = L"flowLayoutPanelFilms";
        this->flowLayoutPanelFilms->Size = System::Drawing::Size(835, 399);
        this->flowLayoutPanelFilms->TabIndex = 0;
        // 
        // label1
        // 
        this->label1->AutoSize = true;
        this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->label1->Location = System::Drawing::Point(228, 56);
        this->label1->Name = L"label1";
        this->label1->Size = System::Drawing::Size(364, 55);
        this->label1->TabIndex = 1;
        this->label1->Text = L"FILM LIBRARY";
        // 
        // profile_btn
        // 
        this->profile_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->profile_btn->Location = System::Drawing::Point(697, 13);
        this->profile_btn->Name = L"profile_btn";
        this->profile_btn->Size = System::Drawing::Size(128, 31);
        this->profile_btn->TabIndex = 2;
        this->profile_btn->Text = L"Profile";
        this->profile_btn->UseVisualStyleBackColor = true;
        this->profile_btn->Click += gcnew System::EventHandler(this, &MainWindow::profile_btn_Click);
        // 
        // MainWindow
        // 
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(835, 561);
        this->Controls->Add(this->profile_btn);
        this->Controls->Add(this->label1);
        this->Controls->Add(this->flowLayoutPanelFilms);
        this->Name = L"MainWindow";
        this->Text = L"MainWindow";
        this->Load += gcnew System::EventHandler(this, &MainWindow::MainWindow_Load);
        this->ResumeLayout(false);
        this->PerformLayout();

    }
#pragma endregion
public: void ShowFilms() {
    flowLayoutPanelFilms->Controls->Clear();
    for (int i = 0; i < filmLibrary->get_films().size(); ++i) {
        const Film film = filmLibrary->get_films()[i];

        Panel^ filmCard = gcnew Panel();
        filmCard->Width = 400;
        filmCard->Height = 350;
        filmCard->BackColor = Color::White;
        filmCard->BorderStyle = BorderStyle::FixedSingle;

        PictureBox^ poster = gcnew PictureBox();
        poster->Width = 225;
        poster->Height = 150;
        poster->SizeMode = PictureBoxSizeMode::Zoom;
        poster->Location = Point(90, 10);

        System::String^ imagePath = gcnew System::String
        (film.get_image().c_str());
        poster->Image = Image::FromFile(imagePath);
        filmCard->Controls->Add(poster);

        Label^ title = gcnew Label();
        title->Text = gcnew System::String(film.get_film_name().c_str());
        title->Font = gcnew System::Drawing::Font("Arial", 10,
            System::Drawing::FontStyle::Bold);
        int x = (filmCard->Width - title->Width) / 2;
        title->Location = Point(x, 170);
        filmCard->Controls->Add(title);

        Label^ details = gcnew Label();
        details->Text = String::Format(
            " Genre: {0}\n Director: {1}\n Country of release: {2}\n Year of release: {3}",
            gcnew System::String(film.get_film_genre().c_str()),
            gcnew System::String(film.get_director().toString().c_str()),
            gcnew System::String(film.get_country().c_str()),
            film.get_year());
        details->Font = gcnew System::Drawing::Font("Arial", 12,
            System::Drawing::FontStyle::Regular);
        details->Location = Point(10, 200);
        details->AutoSize = true;
        filmCard->Controls->Add(details);

        CheckBox^ addToFavorites = gcnew CheckBox();
        addToFavorites->Text = "Favorites";
        addToFavorites->Font = gcnew System::Drawing::Font("Arial", 12,
            System::Drawing::FontStyle::Regular);
        addToFavorites->Location = Point(50, 300);
        addToFavorites->Tag = i;
        addToFavorites->CheckedChanged += gcnew EventHandler(this, &MainWindow::AddToFavorites_CheckedChanged);
        filmCard->Controls->Add(addToFavorites);

        CheckBox^ addToWatched = gcnew CheckBox();
        addToWatched->Text = "Watched";
        addToWatched->Font = gcnew System::Drawing::Font("Arial", 12,
            System::Drawing::FontStyle::Regular);
        addToWatched->Location = Point(250, 300);
        addToWatched->Tag = i;
        addToWatched->CheckedChanged += gcnew EventHandler(this, &MainWindow::AddToWatched_CheckedChanged);
        filmCard->Controls->Add(addToWatched);

        flowLayoutPanelFilms->Controls->Add(filmCard);
    }
}
private: void AddToFavorites_CheckedChanged(Object^ sender, EventArgs^ e) {
    CheckBox^ checkBox = (CheckBox^)sender;
    int filmIndex = (int)checkBox->Tag;

    try {
        const Film* film = &filmLibrary->get_films()[filmIndex];
        filmLibrary->update_user_favorites(_user->get_login(), film);
    }
    catch (const std::exception& ex) {
        checkBox->Checked = false;
        System::Windows::Forms::MessageBox::Show(
            gcnew System::String(ex.what()), "Error",
            System::Windows::Forms::MessageBoxButtons::OK,
            System::Windows::Forms::MessageBoxIcon::Error);
    }
}

private: void AddToWatched_CheckedChanged(Object^ sender, EventArgs^ e) {
    CheckBox^ checkBox = (CheckBox^)sender;
    int filmIndex = (int)checkBox->Tag;

    try {
        const Film* film = &filmLibrary->get_films()[filmIndex];
        filmLibrary->update_user_watched(_user->get_login(), film);
    }
    catch (const std::exception& ex) {
        checkBox->Checked = false;
        System::Windows::Forms::MessageBox::Show(
            gcnew System::String(ex.what()), "Error",
            System::Windows::Forms::MessageBoxButtons::OK,
            System::Windows::Forms::MessageBoxIcon::Error);
    }
}
private: System::Void MainWindow_Load
       (System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void profile_btn_Click
       (System::Object^ sender, System::EventArgs^ e) {
    filmLibrary->save_users_to_file("C:\\git\\Film_library\\users.txt");
    User* user = filmLibrary->find_user(_user->get_login());
    ProfileWindow^ window = gcnew ProfileWindow(user, this);
    window->Owner = this;
    this->Hide();
    window->ShowDialog(this);
}
};
}  // namespace CppCLRWinFormsProject
