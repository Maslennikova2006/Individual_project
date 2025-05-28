// Copyright 2025 Maslennikova Mary

#pragma once
#include <msclr/marshal_cppstd.h>

#include <fstream>
#include <iostream>
#include <string>

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
private: TVector<Film>* films;
       User* _user;
public:
    MainWindow(User* user) {
        InitializeComponent();
        films = new TVector<Film>();
        _user = user;
        LoadFilms();
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
        this->flowLayoutPanelFilms =
            (gcnew System::Windows::Forms::FlowLayoutPanel());
        this->label1 = (gcnew System::Windows::Forms::Label());
        this->SuspendLayout();
        //
        // flowLayoutPanelFilms
        //
        this->flowLayoutPanelFilms->AutoScroll = true;
        this->flowLayoutPanelFilms->Location = System::Drawing::Point(0, 162);
        this->flowLayoutPanelFilms->Name = L"flowLayoutPanelFilms";
        this->flowLayoutPanelFilms->Size = System::Drawing::Size(786, 399);
        this->flowLayoutPanelFilms->TabIndex = 0;
        //
        // label1
        //
        this->label1->AutoSize = true;
        this->label1->Font = (gcnew System::Drawing::Font(
            L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold,
            System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(204)));
        this->label1->Location = System::Drawing::Point(228, 56);
        this->label1->Name = L"label1";
        this->label1->Size = System::Drawing::Size(364, 55);
        this->label1->TabIndex = 1;
        this->label1->Text = L"FILM LIBRARY";
        //
        // MainWindow
        //
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(787, 561);
        this->Controls->Add(this->label1);
        this->Controls->Add(this->flowLayoutPanelFilms);
        this->Name = L"MainWindow";
        this->Text = L"MainWindow";
        this->Load += gcnew System::EventHandler(this,
            &MainWindow::MainWindow_Load);
        this->ResumeLayout(false);
        this->PerformLayout();
    }
#pragma endregion
public: void LoadFilms() {
    std::ifstream file("C:\\git\\Film_library\\films.txt");
    if (!file.is_open()) {
        System::Windows::Forms::MessageBox::Show(
            "The file films.txt not found!", "Error",
            System::Windows::Forms::MessageBoxButtons::OK,
            System::Windows::Forms::MessageBoxIcon::Error);
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        TVector<std::string> parts;
        size_t start = 0;
        size_t end = line.find('|');

        while (end != std::string::npos) {
            parts.push_back(line.substr(start, end - start));
            start = end + 1;
            end = line.find('|', start);
        }
        parts.push_back(line.substr(start));

        Film new_film(parts[0], parts[1], parts[2],
            std::stoi(parts[3]), parts[4]);
        films->push_back(new_film);
    }
    file.close();
}
public: void ShowFilms() {
    flowLayoutPanelFilms->Controls->Clear();

    for (size_t i = 0; i < films->size(); ++i) {
        Film& film = (*films)[i];

        Panel^ filmCard = gcnew Panel();
        filmCard->Width = 250;
        filmCard->Height = 300;
        filmCard->BackColor = Color::White;
        filmCard->BorderStyle = BorderStyle::FixedSingle;

        PictureBox^ poster = gcnew PictureBox();
        poster->Width = 225;
        poster->Height = 150;
        poster->SizeMode = PictureBoxSizeMode::Zoom;
        poster->Location = Point(10, 10);

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
            " Genre: {0}\n Country of release: {1}\n Year of release: {2}",
            gcnew System::String(film.get_film_genre().c_str()),
            gcnew System::String(film.get_country().c_str()),
            film.get_year());
        details->Font = gcnew System::Drawing::Font("Arial", 12,
            System::Drawing::FontStyle::Regular);
        details->Location = Point(10, 200);
        details->AutoSize = true;
        filmCard->Controls->Add(details);

        flowLayoutPanelFilms->Controls->Add(filmCard);
    }
}
private: System::Void MainWindow_Load
       (System::Object^ sender, System::EventArgs^ e) {
}
};
}  // namespace CppCLRWinFormsProject
