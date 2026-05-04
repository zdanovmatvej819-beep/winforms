#pragma once
namespace CppCLRWinFormsProject {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class Form1 : public System::Windows::Forms::Form
    {
    private:
        System::ComponentModel::Container^ components;
        TabControl^ tabControl1;
        TabPage^ tabPage1, ^ tabPage2, ^ tabPage3;
        Panel^ pnlSwitchBorder;
        RadioButton^ rbCalc, ^ rbTheory;
        Panel^ pnlCalc;
        PictureBox^ pbTextIcon, ^ pbKeyIcon, ^ pbResultIcon, ^ pbHexIcon, ^ pbMassIcon;
        Label^ lblInput, ^ lblKey, ^ lblResult, ^ lblHex, ^ lblMass;
        TextBox^ txtInput, ^ txtKey, ^ txtResult, ^ txtHex, ^ txtMass;
        Label^ lblBitTitle, ^ lblDescIn, ^ lblDescKey, ^ lblXorBetween, ^ lblXorLabel, ^ lblDescRes;
        Label^ lampIn, ^ lampKey, ^ lampRes;
        cli::array<Panel^>^ bitsIn, ^ bitsKey, ^ bitsRes;
        Panel^ pnlResetBtn, ^ pnlToggleBtn;
        PictureBox^ pbReset, ^ pbToggle;
        Label^ lblResetBtn, ^ lblToggleBtn;
        Panel^ pnlTheory;
        // --- Атбаш ---
        TextBox^ txtAtbashIn;
        TextBox^ txtAtbashOut;
        Label^ lblAtbashIn;
        Label^ lblAtbashOut;
        Button^ btnLang;
        Button^ btnAtbashRun;
        PictureBox^ pbAtbashIn;
        PictureBox^ pbAtbashOut;
        // --- Атбаш переключение ---
        Panel^ pnlAtbashSwitchBorder;
        RadioButton^ rbAtbashCalc, ^ rbAtbashTheory;
        Panel^ pnlAtbashCalc;

        Panel^ pnlAtbashTheory;


        // текущий язык
        bool isRussian = true;

        static Color CLR_OFF = Color::FromArgb(85, 85, 85);
        static Color CLR_IN_ON = Color::FromArgb(58, 143, 216);
        static Color CLR_KEY_0 = Color::FromArgb(48, 96, 176);
        static Color CLR_KEY_1 = Color::FromArgb(224, 128, 32);
        static Color CLR_RES_ON = Color::FromArgb(46, 204, 46);
        static Color CLR_ACCENT = Color::FromArgb(30, 100, 180);
        static Color CLR_ORANGE = Color::FromArgb(224, 128, 32);
        static Color CLR_BG_DARK = Color::FromArgb(28, 42, 70);

    public:
        Form1(void) {
            InitializeComponent();

            rbCalc->Checked = true;
            ShowCalcPanel();
            BuildTheoryPanel();
            BuildAtbashTheory();
            LoadIcons();
            BuildAtbashModernUI();

        }
    protected:
        ~Form1() { if (components) delete components; }

    private:
        // Загружает PNG из папки рядом с exe
        void TryLoad(PictureBox^ pb, String^ fn) {
            try {
                String^ dir = System::IO::Path::GetDirectoryName(
                    System::Reflection::Assembly::GetExecutingAssembly()->Location);
                String^ path = System::IO::Path::Combine(dir, fn);
                if (System::IO::File::Exists(path))
                    pb->Image = Image::FromFile(path);
            }
            catch (...) {}
        }
        void BuildAtbashModernUI()
        {
            pnlAtbashCalc->Controls->Clear();

            TableLayoutPanel^ root = gcnew TableLayoutPanel();
            root->Dock = DockStyle::Fill;
            root->ColumnCount = 2;
            root->RowCount = 1;
            root->Padding = Padding(15);
            root->BackColor = Color::White;

            root->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 60));
            root->ColumnStyles->Add(gcnew ColumnStyle(SizeType::Percent, 40));

            pnlAtbashCalc->Controls->Add(root);

            // ===== LEFT =====
            Panel^ leftCard = gcnew Panel();
            leftCard->Dock = DockStyle::Fill;
            leftCard->BackColor = Color::FromArgb(245, 247, 250);
            leftCard->Padding = Padding(15);
            leftCard->BorderStyle = BorderStyle::FixedSingle;

            root->Controls->Add(leftCard, 0, 0);

            TableLayoutPanel^ io = gcnew TableLayoutPanel();
            io->Dock = DockStyle::Top;
            io->AutoSize = true;
            io->RowCount = 5;
            io->ColumnCount = 1;

            leftCard->Controls->Add(io);

            Label^ title = gcnew Label();
            title->Text = L"Шифр Атбаш";
            title->Font = gcnew System::Drawing::Font(L"Segoe UI", 16, FontStyle::Bold);
            title->AutoSize = true;

            Label^ lblIn = gcnew Label();
            lblIn->Text = L"Входной текст";
            lblIn->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);

            txtAtbashIn = gcnew TextBox();
            txtAtbashIn->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
            txtAtbashIn->Height = 30;
            txtAtbashIn->TextChanged += gcnew EventHandler(this, &Form1::OnAtbashRun);

            Label^ lblOut = gcnew Label();
            lblOut->Text = L"Результат";
            lblOut->Font = gcnew System::Drawing::Font(L"Segoe UI", 9);

            txtAtbashOut = gcnew TextBox();
            txtAtbashOut->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
            txtAtbashOut->ReadOnly = true;
            txtAtbashOut->BackColor = Color::FromArgb(240, 240, 240);
            txtAtbashOut->Height = 30;

            io->Controls->Add(title);
            io->Controls->Add(lblIn);
            io->Controls->Add(txtAtbashIn);
            io->Controls->Add(lblOut);
            io->Controls->Add(txtAtbashOut);

            // ===== RIGHT =====
            Panel^ rightCard = gcnew Panel();
            rightCard->Dock = DockStyle::Fill;
            rightCard->BackColor = Color::FromArgb(250, 250, 252);
            rightCard->Padding = Padding(15);
            rightCard->BorderStyle = BorderStyle::FixedSingle;

            root->Controls->Add(rightCard, 1, 0);

            FlowLayoutPanel^ fl = gcnew FlowLayoutPanel();
            fl->Dock = DockStyle::Top;
            fl->FlowDirection = FlowDirection::TopDown;
            fl->AutoSize = true;

            rightCard->Controls->Add(fl);

            btnLang = gcnew Button();
            btnLang->Text = L"RU / EN";
            btnLang->Width = 160;
            btnLang->Height = 40;
            btnLang->BackColor = Color::FromArgb(30, 100, 180);
            btnLang->ForeColor = Color::White;
            btnLang->FlatStyle = FlatStyle::Flat;
            btnLang->Click += gcnew EventHandler(this, &Form1::OnLangToggle);

            btnAtbashRun = gcnew Button();
            btnAtbashRun->Text = L"Шифровать";
            btnAtbashRun->Width = 160;
            btnAtbashRun->Height = 40;
            btnAtbashRun->BackColor = Color::FromArgb(0, 150, 120);
            btnAtbashRun->ForeColor = Color::White;
            btnAtbashRun->FlatStyle = FlatStyle::Flat;
            btnAtbashRun->Click += gcnew EventHandler(this, &Form1::OnAtbashRun);

            fl->Controls->Add(btnLang);
            fl->Controls->Add(btnAtbashRun);
        }

        void LoadIcons() {
            TryLoad(pbTextIcon, L"pbText.png");
            TryLoad(pbKeyIcon, L"pbKeyIcon.png");
            TryLoad(pbResultIcon, L"pbResult.png");
            TryLoad(pbHexIcon, L"pbResultHex.png");
            TryLoad(pbMassIcon, L"pbMass.png");
            TryLoad(pbReset, L"pbReset.png");
            TryLoad(pbToggle, L"pbHintToggle.png");

        }

        // Загружает PNG инфографики из папки рядом с exe, возвращает Image^ или nullptr
        Image^ LoadInfographic(String^ fn) {
            try {
                String^ dir = System::IO::Path::GetDirectoryName(
                    System::Reflection::Assembly::GetExecutingAssembly()->Location);
                String^ path = System::IO::Path::Combine(dir, fn);
                if (System::IO::File::Exists(path))
                    return Image::FromFile(path);
            }
            catch (...) {}
            return nullptr;
        }

    private:
        String^ Atbash(String^ input) {

            String^ ruU = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
            String^ ruL = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

            String^ enU = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            String^ enL = L"abcdefghijklmnopqrstuvwxyz";

            System::Text::StringBuilder^ res = gcnew System::Text::StringBuilder();

            for each (wchar_t ch in input) {

                if (isRussian) {
                    int i = ruU->IndexOf(ch);
                    if (i != -1) {
                        res->Append(ruU[ruU->Length - 1 - i]);
                        continue;
                    }

                    i = ruL->IndexOf(ch);
                    if (i != -1) {
                        res->Append(ruL[ruL->Length - 1 - i]);
                        continue;
                    }
                }
                else {
                    int i = enU->IndexOf(ch);
                    if (i != -1) {
                        res->Append(enU[enU->Length - 1 - i]);
                        continue;
                    }

                    i = enL->IndexOf(ch);
                    if (i != -1) {
                        res->Append(enL[enL->Length - 1 - i]);
                        continue;
                    }
                }

                // если символ не из алфавита
                res->Append(ch);
            }

            return res->ToString();
        }
        void InitializeComponent(void) {
            components = gcnew System::ComponentModel::Container();
            SuspendLayout();
            Text = L"Программно-методический комплекс: Классическая криптография";
            ClientSize = System::Drawing::Size(1040, 720);
            FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            StartPosition = FormStartPosition::CenterScreen;
            BackColor = Color::White;
            Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);

            tabControl1 = gcnew TabControl();
            tabControl1->Dock = DockStyle::Fill;
            tabControl1->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);
            tabPage1 = gcnew TabPage(L"Модуль 1: Шифр Атбаш");
            // === Переключатель режимов (как XOR) ===
            pnlAtbashSwitchBorder = gcnew Panel();
            pnlAtbashSwitchBorder->Location = Point(8, 6);
            pnlAtbashSwitchBorder->Size = System::Drawing::Size(520, 34);
            pnlAtbashSwitchBorder->BorderStyle = BorderStyle::FixedSingle;
            pnlAtbashSwitchBorder->BackColor = Color::FromArgb(240, 240, 240);

            rbAtbashCalc = gcnew RadioButton();
            rbAtbashCalc->Text = L"Калькулятор";
            rbAtbashCalc->Location = Point(6, 7);
            rbAtbashCalc->Size = System::Drawing::Size(150, 20);
            rbAtbashCalc->Checked = true;
            rbAtbashCalc->CheckedChanged += gcnew EventHandler(this, &Form1::rbAtbashCalc_CC);

            rbAtbashTheory = gcnew RadioButton();
            rbAtbashTheory->Text = L"Теоретические сведения";
            rbAtbashTheory->Location = Point(200, 7);
            rbAtbashTheory->AutoSize = true;
            rbAtbashTheory->CheckedChanged += gcnew EventHandler(this, &Form1::rbAtbashTheory_CC);

            pnlAtbashSwitchBorder->Controls->Add(rbAtbashCalc);
            pnlAtbashSwitchBorder->Controls->Add(rbAtbashTheory);

            tabPage1->Controls->Add(pnlAtbashSwitchBorder);
            // ====================== АТБАШ UI ======================

// Ввод
            pnlAtbashCalc = gcnew Panel();
            pnlAtbashCalc->Location = Point(8, 48);
            pnlAtbashTheory = gcnew Panel();
            pnlAtbashTheory->Location = Point(8, 48);
            pnlAtbashTheory->Size = System::Drawing::Size(1020, 650);
            pnlAtbashTheory->BackColor = Color::FromArgb(28, 42, 70);
            pnlAtbashTheory->Visible = false;


            tabPage1->Controls->Add(pnlAtbashTheory);
            pnlAtbashCalc->Size = System::Drawing::Size(1020, 650);
            pnlAtbashCalc->BackColor = Color::White;

            tabPage1->Controls->Add(pnlAtbashCalc);
            lblAtbashIn = gcnew Label();
            lblAtbashIn->Text = L"Исходный текст:";
            lblAtbashIn->Location = Point(20, 20);
            lblAtbashIn->Size = System::Drawing::Size(200, 20);

            txtAtbashIn = gcnew TextBox();
            
            txtAtbashIn->Location = Point(40, 45);
            txtAtbashIn->Size = System::Drawing::Size(300, 28);

            // Вывод
            lblAtbashOut = gcnew Label();
            lblAtbashOut->Text = L"Результат:";
            lblAtbashOut->Location = Point(20, 85);
            lblAtbashOut->Size = System::Drawing::Size(200, 20);

            txtAtbashOut = gcnew TextBox();
            txtAtbashOut->Location = Point(40, 110);
            txtAtbashOut->Size = System::Drawing::Size(300, 28);
            txtAtbashOut->ReadOnly = true;
            txtAtbashOut->BackColor = Color::FromArgb(245, 245, 245);

            // КНОПКА ЯЗЫКА (вот она!)
            btnLang = gcnew Button();
            btnLang->Text = L"Русский";
            btnLang->Location = Point(340, 45);
            btnLang->Size = System::Drawing::Size(120, 30);
            btnLang->Click += gcnew EventHandler(this, &Form1::OnLangToggle);
            btnLang->FlatStyle = FlatStyle::Flat;
            btnLang->BackColor = Color::FromArgb(30, 100, 180);
            btnLang->ForeColor = Color::White;
            btnLang->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5f, FontStyle::Bold);
            btnLang->FlatAppearance->BorderSize = 0;
            btnAtbashRun = gcnew Button();
            btnAtbashRun->Text = L"Шифровать / Дешифровать";
            btnAtbashRun->Location = Point(340, 85);
            btnAtbashRun->Size = System::Drawing::Size(180, 30);

            btnAtbashRun->FlatStyle = FlatStyle::Flat;
            btnAtbashRun->BackColor = Color::FromArgb(30, 100, 180);
            btnAtbashRun->ForeColor = Color::White;
            btnAtbashRun->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Bold);
            btnAtbashRun->FlatAppearance->BorderSize = 0;

            btnAtbashRun->Click += gcnew EventHandler(this, &Form1::OnAtbashRun);

            // добавляем элементы на вкладку
            Panel^ card = gcnew Panel();
            card->Location = Point(20, 20);

            card->BackColor = Color::FromArgb(245, 247, 250);
            card->BorderStyle = BorderStyle::FixedSingle;
            card->AutoSize = true;
            card->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;

            pnlAtbashCalc->Controls->Add(card);
            pbAtbashIn = MkPB(10, 45, 24, 24);
            pbAtbashOut = MkPB(10, 110, 24, 24);

            card->Controls->Add(lblAtbashIn);
            card->Controls->Add(txtAtbashIn);
            card->Controls->Add(lblAtbashOut);
            card->Controls->Add(txtAtbashOut);
            card->Controls->Add(btnLang);
            card->Controls->Add(btnAtbashRun);
            card->Controls->Add(pbAtbashIn);
            card->Controls->Add(pbAtbashOut);

            // события
            tabPage2 = gcnew TabPage(L"Модуль 2: Шифр Виженера");
            tabPage3 = gcnew TabPage(L"Модуль 3: Шифр XOR");
            tabControl1->TabPages->Add(tabPage1);
            tabControl1->TabPages->Add(tabPage2);
            tabControl1->TabPages->Add(tabPage3);
            tabControl1->SelectedIndex = 2;

            pnlSwitchBorder = gcnew Panel();
            pnlSwitchBorder->Location = Point(8, 6);
            pnlSwitchBorder->Size = System::Drawing::Size(520, 34);
            pnlSwitchBorder->BorderStyle = BorderStyle::FixedSingle;
            pnlSwitchBorder->BackColor = Color::FromArgb(240, 240, 240);
            rbCalc = gcnew RadioButton();
            rbCalc->Text = L"Побитовый калькулятор";
            rbCalc->Location = Point(6, 7); rbCalc->Size = System::Drawing::Size(200, 20);
            rbCalc->ForeColor = Color::FromArgb(0, 160, 0);
            rbCalc->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Bold);
            rbCalc->CheckedChanged += gcnew EventHandler(this, &Form1::rbCalc_CC);
            rbTheory = gcnew RadioButton();
            rbTheory->Text = L"ⓘ  Теоретические сведения";
            rbTheory->Location = Point(220, 7); rbTheory->Size = System::Drawing::Size(220, 20);
            rbTheory->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);
            rbTheory->CheckedChanged += gcnew EventHandler(this, &Form1::rbTheory_CC);
            pnlSwitchBorder->Controls->Add(rbCalc);
            pnlSwitchBorder->Controls->Add(rbTheory);
            tabPage3->Controls->Add(pnlSwitchBorder);

            pnlCalc = gcnew Panel();
            pnlCalc->Location = Point(8, 48);
            pnlCalc->Size = System::Drawing::Size(1020, 650);
            pnlCalc->BackColor = Color::White;

            // ---- Левая колонка ----
            const int LX = 10, IW = 52, IH = 52, FX = 70, FW = 200;

            pbTextIcon = MkPB(LX, 8, IW, IH);
            lblInput = MkLbl(L"Исходный текст (ASCII):", FX, 10, FW, 16);
            lblInput->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5f);
            txtInput = MkTB(FX, 28, FW, 28);
            txtInput->Font = gcnew System::Drawing::Font(L"Courier New", 9.5f);
            txtInput->TextChanged += gcnew EventHandler(this, &Form1::OnInput);

            pbKeyIcon = MkPB(LX, 74, IW, IH);
            lblKey = MkLbl(L"Ключ (ASCII):", FX, 76, FW, 16);
            lblKey->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5f);
            txtKey = MkTB(FX, 94, FW, 28);
            txtKey->Font = gcnew System::Drawing::Font(L"Courier New", 9.5f);
            txtKey->TextChanged += gcnew EventHandler(this, &Form1::OnInput);

            pbResultIcon = MkPB(LX, 146, IW, IH);
            lblResult = MkLbl(L"Результат XOR:", FX, 148, FW + 30, 16);
            lblResult->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5f, FontStyle::Bold);
            txtResult = MkTB(FX, 166, FW, 28);
            txtResult->ReadOnly = true; txtResult->BackColor = Color::FromArgb(248, 248, 248);
            txtResult->Font = gcnew System::Drawing::Font(L"Courier New", 9.0f);

            pbHexIcon = MkPB(LX, 204, IW, IH);
            lblHex = MkLbl(L"НЕХ-представление результата:", FX, 206, FW + 30, 16);
            lblHex->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5f, FontStyle::Bold);
            txtHex = MkTB(FX, 224, 90, 28);
            txtHex->ReadOnly = true; txtHex->BackColor = Color::FromArgb(248, 248, 248);
            txtResult->Font = gcnew System::Drawing::Font(L"Courier New", 9.0f);

            pbMassIcon = MkPB(LX, 262, IW, IH);
            lblMass = MkLbl(L"Итоговый массив шифротекста (DEC):", FX, 264, FW + 30, 16);
            lblMass->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5f, FontStyle::Bold);
            txtMass = MkTB(FX, 282, FW, 28);
            txtMass->ReadOnly = true; txtMass->BackColor = Color::FromArgb(248, 248, 248);
            txtMass->Font = gcnew System::Drawing::Font(L"Courier New", 9.5f);

            for each(Control ^ c in gcnew cli::array<Control^>{
                pbTextIcon, lblInput, txtInput, pbKeyIcon, lblKey, txtKey,
                    pbResultIcon, lblResult, txtResult, pbHexIcon, lblHex, txtHex,
                    pbMassIcon, lblMass, txtMass})
                pnlCalc->Controls->Add(c);

            // ---- Центр: биты ----
                        // ---- Центр: биты ----
                        // ---- Центр: биты ----
            const int BX = 370, BY = 4, CELL = 28, GAP = 3;
            const int DESC_W = 82, BITS_X = BX + DESC_W + 8;

            lblBitTitle = MkLbl(L"ВЕРТИКАЛЬНЫЙ СТЕК БИТОВ (Первый символ)", 320, BY, 460, 16);  // ИЗМЕНЕНО: 370 -> 290
            lblBitTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5f, FontStyle::Bold);
            lblBitTitle->TextAlign = ContentAlignment::MiddleCenter;
            pnlCalc->Controls->Add(lblBitTitle);
            int RY_IN = BY + 22;
            lblDescIn = MkLbl(L"БИТЫ ТЕКСТА\n(00000000):", BX, RY_IN + 2, DESC_W, 32);
            lblDescIn->Font = gcnew System::Drawing::Font(L"Segoe UI", 7.5f);
            bitsIn = gcnew cli::array<Panel^>(8);
            for (int i = 0; i < 8; i++) bitsIn[i] = MkBit(BITS_X + i * (CELL + GAP), RY_IN, CELL, CLR_OFF, L"0");
            lampIn = MkLbl(L"💡", BITS_X + 8 * (CELL + GAP) + 4, RY_IN + 4, 22, 22);
            pnlCalc->Controls->Add(lblDescIn);
            for each(Panel ^ p in bitsIn) pnlCalc->Controls->Add(p);
            pnlCalc->Controls->Add(lampIn);

            int RY_XB = RY_IN + CELL + 5;
            int bbW = 8 * (CELL + GAP) - GAP, xsW = 30, xsX = BITS_X + bbW / 2 - xsW / 2;
            lblXorBetween = MkLbl(L"⊕", xsX, RY_XB, xsW, 22);
            lblXorBetween->Font = gcnew System::Drawing::Font(L"Segoe UI", 14.0f, FontStyle::Bold);
            lblXorBetween->ForeColor = Color::FromArgb(50, 50, 50);
            lblXorBetween->TextAlign = ContentAlignment::MiddleCenter;
            pnlCalc->Controls->Add(lblXorBetween);

            int RY_KEY = RY_XB + 24;
            lblDescKey = MkLbl(L"БИТЫ КЛЮЧА\n(00000000):", BX, RY_KEY + 2, DESC_W, 32);
            lblDescKey->Font = gcnew System::Drawing::Font(L"Segoe UI", 7.5f);
            bitsKey = gcnew cli::array<Panel^>(8);
            for (int i = 0; i < 8; i++) bitsKey[i] = MkBit(BITS_X + i * (CELL + GAP), RY_KEY, CELL, CLR_OFF, L"0");
            lampKey = MkLbl(L"💡", BITS_X + 8 * (CELL + GAP) + 4, RY_KEY + 4, 22, 22);
            pnlCalc->Controls->Add(lblDescKey);
            for each(Panel ^ p in bitsKey) pnlCalc->Controls->Add(p);
            pnlCalc->Controls->Add(lampKey);

            int RY_XL = RY_KEY + CELL + 4;
            lblXorLabel = MkLbl(L"⊕  (Исключающее ИЛИ)", BITS_X, RY_XL, 260, 18);
            lblXorLabel->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);
            lblXorLabel->ForeColor = Color::FromArgb(80, 80, 80);
            pnlCalc->Controls->Add(lblXorLabel);

            int RY_RES = RY_XL + 22;
            lblDescRes = MkLbl(L"РЕЗУЛЬТАТ\n(00000000):", BX, RY_RES + 2, DESC_W, 32);
            lblDescRes->Font = gcnew System::Drawing::Font(L"Segoe UI", 7.5f);
            bitsRes = gcnew cli::array<Panel^>(8);
            for (int i = 0; i < 8; i++) {
                bitsRes[i] = MkBit(BITS_X + i * (CELL + GAP), RY_RES, CELL, CLR_OFF, L"0");
                bitsRes[i]->Cursor = Cursors::Hand;
                bitsRes[i]->Click += gcnew EventHandler(this, &Form1::OnResBit);
            }
            lampRes = MkLbl(L"💡", BITS_X + 8 * (CELL + GAP) + 4, RY_RES + 4, 22, 22);
            pnlCalc->Controls->Add(lblDescRes);
            for each(Panel ^ p in bitsRes) pnlCalc->Controls->Add(p);
            pnlCalc->Controls->Add(lampRes);

            // ---- Правая колонка ----
            const int RX = 810, BW = 150, BH = 70;
            pnlResetBtn = MkBtnPanel(RX, 8, BW, BH);
            pnlResetBtn->Click += gcnew EventHandler(this, &Form1::OnReset);
            pbReset = MkPB(6, 6, 48, 48); pbReset->Cursor = Cursors::Hand;
            pbReset->Click += gcnew EventHandler(this, &Form1::OnReset);
            lblResetBtn = gcnew Label();
            lblResetBtn->Text = L"   Сбросить";
            lblResetBtn->Location = Point(60, 12); lblResetBtn->Size = System::Drawing::Size(96, 40);
            lblResetBtn->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5f, FontStyle::Bold);
            lblResetBtn->ForeColor = Color::FromArgb(30, 30, 30);
            lblResetBtn->TextAlign = ContentAlignment::MiddleLeft;
            lblResetBtn->Cursor = Cursors::Hand;
            lblResetBtn->Click += gcnew EventHandler(this, &Form1::OnReset);
            pnlResetBtn->Controls->Add(pbReset); pnlResetBtn->Controls->Add(lblResetBtn);
            pnlCalc->Controls->Add(pnlResetBtn);

            pnlToggleBtn = MkBtnPanel(RX, 8 + BH + 14, BW, BH);
            pnlToggleBtn->Click += gcnew EventHandler(this, &Form1::OnToggle);
            pbToggle = MkPB(6, 6, 48, 48); pbToggle->Cursor = Cursors::Hand;
            pbToggle->Click += gcnew EventHandler(this, &Form1::OnToggle);
            lblToggleBtn = gcnew Label();
            lblToggleBtn->Text = L"Переключить          бит\n(Инверсия 0 ⇌ 1)";
            lblToggleBtn->Location = Point(60, 12); lblToggleBtn->Size = System::Drawing::Size(96, 40);
            lblToggleBtn->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5f, FontStyle::Bold);
            lblToggleBtn->ForeColor = Color::FromArgb(30, 30, 30);
            lblToggleBtn->TextAlign = ContentAlignment::MiddleLeft;
            lblToggleBtn->Cursor = Cursors::Hand;
            lblToggleBtn->Click += gcnew EventHandler(this, &Form1::OnToggle);
            pnlToggleBtn->Controls->Add(pbToggle); pnlToggleBtn->Controls->Add(lblToggleBtn);
            pnlCalc->Controls->Add(pnlToggleBtn);

            tabPage3->Controls->Add(pnlCalc);

            pnlTheory = gcnew Panel();
            pnlTheory->Location = Point(8, 48);
            pnlTheory->Size = System::Drawing::Size(1020, 650);
            pnlTheory->BackColor = CLR_BG_DARK;
            pnlTheory->Visible = false;
            tabPage3->Controls->Add(pnlTheory);

            Controls->Add(tabControl1);
            ResumeLayout(false);
        }

        // =====================================================================
        //  ФАБРИКИ
        // =====================================================================
    private:
        Label^ MkLbl(String^ t, int x, int y, int w, int h) {
            Label^ l = gcnew Label(); l->Text = t; l->Location = Point(x, y);
            l->Size = System::Drawing::Size(w, h); l->AutoSize = false; return l;
        }
        TextBox^ MkTB(int x, int y, int w, int h) {
            TextBox^ t = gcnew TextBox(); t->Location = Point(x, y);
            t->Size = System::Drawing::Size(w, h); t->BorderStyle = BorderStyle::FixedSingle; return t;
        }
        PictureBox^ MkPB(int x, int y, int w, int h) {
            PictureBox^ p = gcnew PictureBox(); p->Location = Point(x, y);
            p->Size = System::Drawing::Size(w, h); p->SizeMode = PictureBoxSizeMode::Zoom;
            p->BackColor = Color::Transparent; return p;
        }
        Panel^ MkBit(int x, int y, int sz, Color bg, String^ t) {
            Panel^ p = gcnew Panel(); p->Location = Point(x, y);
            p->Size = System::Drawing::Size(sz, sz); p->BackColor = bg;
            p->BorderStyle = BorderStyle::FixedSingle;
            Label^ l = gcnew Label(); l->Text = t; l->Dock = DockStyle::Fill;
            l->TextAlign = ContentAlignment::MiddleCenter;
            l->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0f, FontStyle::Bold);
            l->ForeColor = Color::White; l->BackColor = Color::Transparent;
            l->Click += gcnew EventHandler(this, &Form1::OnBitLbl);
            p->Controls->Add(l); return p;
        }
        Panel^ MkBtnPanel(int x, int y, int w, int h) {
            Panel^ p = gcnew Panel(); p->Location = Point(x, y);
            p->Size = System::Drawing::Size(w, h);
            p->BackColor = Color::FromArgb(245, 245, 245);
            p->BorderStyle = BorderStyle::FixedSingle; p->Cursor = Cursors::Hand; return p;
        }
        // Универсальный AddLabel для теории
        Label^ AL(Control^ par, String^ t, int x, int y, int w, int h,
            System::Drawing::Font^ f, Color fc, ContentAlignment a) {
            Label^ l = gcnew Label(); l->Text = t; l->Location = Point(x, y);
            l->Size = System::Drawing::Size(w, h); l->Font = f; l->ForeColor = fc;
            l->BackColor = Color::Transparent; l->TextAlign = a; l->AutoSize = false;
            par->Controls->Add(l); return l;
        }

        // =====================================================================
        //  ПАНЕЛЬ ТЕОРИИ
        // =====================================================================
    private:
        void BuildTheoryPanel() {
            Panel^ scroll = gcnew Panel();
            scroll->Dock = DockStyle::Fill; scroll->AutoScroll = true;
            scroll->BackColor = CLR_BG_DARK;
            pnlTheory->Controls->Add(scroll);

            Panel^ inn = gcnew Panel();
            inn->Location = Point(0, 0); inn->Width = 990; inn->BackColor = CLR_BG_DARK;
            scroll->Controls->Add(inn);

            int Y = 16, CW = 968;

            // ── Заголовок ────────────────────────────────────────────────
            Panel^ hdr = gcnew Panel(); hdr->Location = Point(10, Y);
            hdr->Size = System::Drawing::Size(CW, 64); hdr->BackColor = CLR_ACCENT;
            inn->Controls->Add(hdr);
            AL(hdr, L"ШИФР XOR — БИТОВЫЕ ОПЕРАЦИИ", 0, 0, CW, 64,
                gcnew System::Drawing::Font(L"Segoe UI", 18.0f, FontStyle::Bold),
                Color::White, ContentAlignment::MiddleCenter);
            Y += 80;

            // ── Раздел 1: Введение ────────────────────────────────────────
            Y = SecTitle(inn, Y, CW, L"1. Введение");
            Y = TxtBlk(inn, Y, CW,
                L"В фундаменте всей современной информационной безопасности лежит парадокс: самые надёжные системы защиты часто опираются на элементарные математические операции. "
                L"Одной из таких операций является «исключающее ИЛИ» (eXclusive OR — XOR). Если представить криптографию как строительство неприступной крепости, то XOR — это "
                L"идеальный кирпич: он дешёв в производстве, обладает предсказуемой формой, но при правильной методике укладки создаёт стену, которую невозможно пробить даже "
                L"лобовой атакой суперкомпьютера.");
            Y = TxtBlk(inn, Y, CW,
                L"Почему мы изучаем XOR в контексте битовых операций? В цифровом мире абсолютно всё — от ваших фотографий до банковских транзакций — представлено в виде "
                L"последовательностей нулей и единиц. Шифр XOR работает непосредственно с этим «генетическим кодом» данных. Актуальность данной темы невозможно переоценить: "
                L"без понимания принципов XOR невозможно осознать работу алгоритмов симметричного шифрования (таких как AES), протоколов сетевой защиты TLS или систем контроля "
                L"целостности данных. Мы разберём, как простая логическая функция превращается в «совершенный шифр», и почему даже величайшие умы XX века считали его вершиной "
                L"криптографической мысли.");

            // ── Раздел 2: История ────────────────────────────────────────
            Y = SecTitle(inn, Y, CW, L"2. История развития и концепция абсолютной секретности");
            Y = TxtBlk(inn, Y, CW,
                L"История XOR-шифрования — это захватывающий путь от механических телетайпов до квантово-стойких алгоритмов. Первое практическое применение метода неразрывно "
                L"связано с именем Гилберта Вернама, инженера лабораторий Bell. В 1917 году, в разгар Первой мировой войны, Вернам искал способ автоматизировать шифрование "
                L"телеграфных сообщений. До этого криптография была медленным ручным процессом, подверженным человеческим ошибкам. Вернам предложил использовать закольцованную "
                L"бумажную ленту с ключом, которая объединялась с лентой сообщения с помощью электромеханического реле, реализующего логику XOR. Это стало рождением технологии, "
                L"позже получившей название «одноразовые блокноты» (One-Time Pad).");
            Y = TxtBlk(inn, Y, CW,
                L"Название метода происходит от реальных бумажных блокнотов, которые выдавались агентам разведки. Каждая страница содержала уникальный ключ — набор случайных "
                L"символов — для шифрования ровно одного сообщения. После использования страница немедленно уничтожалась, что исключало возможность повторного анализа. При "
                L"использовании XOR в этой системе каждый бит сообщения смешивается с соответствующим битом абсолютно случайного ключа, что превращает осмысленное сообщение "
                L"в нечитаемый «белый шум».");
            Y = HlBox(inn, Y, CW,
                L"📜  Исторический нюанс: Шифр, предотвративший катастрофу",
                L"Во времена Холодной войны СССР и США использовали «одноразовые блокноты» на основе XOR для защиты самых чувствительных каналов связи. "
                L"Знаменитый «горячий телефон» между Кремлём и Белым домом, предназначенный для предотвращения ядерного конфликта, защищался именно этим методом. "
                L"Он гарантировал, что даже если противник перехватит сигнал, он не получит ничего, кроме абсолютно случайного шума, не поддающегося анализу. "
                L"Ключи доставлялись дипломатической почтой на магнитных лентах, и эта математическая простота гарантировала невозможность взлома даже самыми мощными суперкомпьютерами.");
            Y = TxtBlk(inn, Y, CW,
                L"Научное обоснование этой технологии появилось в 1949 году, когда Клод Шеннон опубликовал работу «Теория связи в секретных системах». Шеннон математически "
                L"доказал существование «совершенной секретности» — состояния, при котором перехваченный шифротекст не даёт атакующему абсолютно никаких сведений об исходном "
                L"тексте. Согласно Шеннону, для достижения такой неуязвимости шифр XOR должен отвечать трём жёстким критериям:");
            Y = NumList(inn, Y, CW, gcnew cli::array<String^>(3) {
                L"Ключ должен быть не короче самого сообщения.",
                    L"Ключ должен быть абсолютно случайным, полученным из физических процессов (например, атмосферных помех), а не из компьютерных алгоритмов.",
                    L"Ключ никогда не должен использоваться повторно. Если зашифровать два разных сообщения одним ключом, он «аннигилирует» при сравнении текстов, полностью компрометируя защиту."
            });

            // ── Раздел 3: Теория ─────────────────────────────────────────
            Y = SecTitle(inn, Y, CW, L"3. Теоретические основы и математическая модель");
            Y = TxtBlk(inn, Y, CW,
                L"Чтобы понять физику процесса, необходимо спуститься на уровень двоичной логики. Операция «исключающее ИЛИ» (обозначается в математике как ⊕, а в языках "
                L"программирования как символ ^) — это фундамент, на котором держится вся битовая магия. В дискретной математике она определяется как сложение по модулю 2: "
                L"мы складываем два бита и берём остаток от деления суммы на 2. Формально это выглядит следующим образом:");

            // ИНФОГРАФИКА 1: Таблица истинности (PNG)
            Y = InfographicBlock(inn, Y, CW, L"таблица_истинности_.png", 220);

            Y = TxtBlk(inn, Y, CW,
                L"Именно логика «исключения» делает XOR идеально сбалансированным инструментом криптографии: в таблице истинности ровно 50% нулей и 50% единиц. "
                L"Это обеспечивает отсутствие статистического перекоса, что критически важно для сокрытия структуры данных. С точки зрения теории вероятностей, XOR "
                L"работает как «условный инвертор»: если бит ключа равен 0, данные проходят без изменений, если 1 — они инвертируются.");
            Y = TxtBlk(inn, Y, CW,
                L"Самое выдающееся свойство XOR — его самообратимость, или инволюция. Если у нас есть исходное сообщение P (Plaintext) и секретный ключ K (Key), то процесс "
                L"шифрования описывается формулой C = P ⊕ K. Чтобы вернуть исходный текст, нам не нужно изобретать сложную обратную функцию — достаточно применить тот же "
                L"самый ключ к полученному шифротексту ещё раз. Математически это доказывается просто: C ⊕ K = (P ⊕ K) ⊕ K = P ⊕ (K ⊕ K) = P ⊕ 0 = P. Поскольку любое "
                L"число, подвергнутое XOR с самим собой, всегда даёт ноль, ключ «самоуничтожается», оставляя исходные данные нетронутыми. Это делает алгоритм невероятно "
                L"эффективным, позволяя выполнять и зашифровку, и расшифровку одной и той же аппаратной схемой.");
            Y = FmBox(inn, Y, CW, L"C ⊕ K = (P ⊕ K) ⊕ K = P ⊕ (K ⊕ K) = P ⊕ 0 = P");

            // ИНФОГРАФИКА 2: Принцип совершенной секретности (PNG)
            Y = InfographicBlock(inn, Y, CW, L"принцип_совершенной_секретности.png", 160);

            // ── Раздел 4: Алгоритм ───────────────────────────────────────
            Y = SecTitle(inn, Y, CW, L"4. Пошаговый алгоритм");
            Y = TxtBlk(inn, Y, CW, L"Рассмотрим детальную механику работы программного модуля, отвечающего за XOR-преобразование.");

            // ИНФОГРАФИКА 3: Блок-схема алгоритма (PNG)
            Y = InfographicBlock(inn, Y, CW, L"блок_схема_алгоритма.png", 220);

            Y = SubTit(inn, Y, CW, L"Процесс шифрования:");
            Y = NumList(inn, Y, CW, gcnew cli::array<String^>(4) {
                L"Квантование данных: Исходный массив информации (текст, файл или поток) разбивается на байты. Каждый символ интерпретируется в соответствии с выбранной кодировкой (например, UTF-8).",
                    L"Генерация ключевого потока: Создаётся секретный ключ. Если его длина меньше длины сообщения, модуль применяет механизм циклического повторения (Key Wrapping). Например, ключ \"KEY\" превращается в последовательность \"KEYKEYKEY...\".",
                    L"Побитовая итерация: Программа последовательно проходит через каждый байт сообщения, выполняя XOR-сложение текущего байта данных с соответствующим байтом ключа на уровне процессора.",
                    L"Сборка шифротекста: Результаты объединяются в единый бинарный массив. Для удобства передачи или отображения его часто переводят в шестнадцатеричный вид (HEX)."
            });
            Y = SubTit(inn, Y, CW, L"Процесс дешифрования:");
            Y = NumList(inn, Y, CW, gcnew cli::array<String^>(4) {
                L"Приём данных: Загружается массив зашифрованных байтов.",
                    L"Инициализация ключа: Вводится тот же ключ. Важно помнить, что ошибка даже в одном бите ключа сделает невозможным восстановление конкретного символа сообщения.",
                    L"Повторная обработка: Процедура побитового XOR-сложения повторяется. Благодаря свойству инволюции, повторное наложение ключа снимает «маскировку».",
                    L"Декодирование: Полученный массив байтов интерпретируется обратно в исходный формат (например, в читаемую строку)."
            });

            // ── Раздел 5: Пример ─────────────────────────────────────────
            Y = SecTitle(inn, Y, CW, L"5. Практический пример");
            Y = TxtBlk(inn, Y, CW, L"Для наглядности разберём процесс шифрования конкретного слова.");
            Y = HlBox(inn, Y, CW,
                L"📋  Условие задачи",
                L"Сообщение: \"SHANNON\" (7 символов)\nКлюч: \"AXIOM\" (5 символов)");
            Y = TxtBlk(inn, Y, CW, L"Решение:");
            Y = NumList(inn, Y, CW, gcnew cli::array<String^>(4) {
                L"Перевод в ASCII: S(83), H(72), A(65), N(78), N(78), O(79), N(78).",
                    L"Подготовка ключа (циклически): A(65), X(88), I(73), O(79), M(77), A(65), X(88).",
                    L"Побитовая операция (первые три символа):\n'S' ⊕ 'A': 01010011 ⊕ 01000001 = 00010010 (18)\n'H' ⊕ 'X': 01001000 ⊕ 01011000 = 00010000 (16)\n'A' ⊕ 'I': 01000001 ⊕ 01001001 = 00001000 (8)",
                    L"Остальные символы по аналогии: N ⊕ O = 1, N ⊕ M = 3, O ⊕ A = 14, N ⊕ X = 22."
            });

            // ИНФОГРАФИКА 4: Битовый калькулятор (PNG)
            Y = InfographicBlock(inn, Y, CW, L"битовый_калькулятор.png", 160);

            Y = HlBox(inn, Y, CW,
                L"✅  Итоговый массив шифротекста (DEC)",
                L"[ 18, 16, 8, 1, 3, 14, 22 ]\n\nКак видите, результат визуально никак не напоминает оригинал, и без знания ключа восстановить его невозможно.");

            // ── Раздел 6: Заключение ──────────────────────────────────────
            Y = SecTitle(inn, Y, CW, L"6. Заключение");
            Y = TxtBlk(inn, Y, CW,
                L"Подводя итог, можно утверждать, что шифр XOR — это идеальный баланс между математической красотой и предельной практической пользой. Его сильные стороны — "
                L"колоссальная производительность и теоретическая неуязвимость при соблюдении условий Шеннона. Однако у метода есть и своя «ахиллесова пята»: проблема управления "
                L"ключами. В реальных масштабах крайне сложно безопасно передавать абсолютно случайные ключи, равные по длине самому сообщению. При использовании коротких "
                L"повторяющихся ключей шифр становится уязвим для криптоанализа.");
            Y = TxtBlk(inn, Y, CW,
                L"Тем не менее, XOR не ушёл в историю. Он эволюционировал и стал неотъемлемой частью более сложных конструкций, таких как современный стандарт AES или протоколы "
                L"аутентификации. Понимание логики XOR — это ваш пропуск в мир серьёзной криптографии, позволяющий видеть за сложными программными интерфейсами элегантную "
                L"механику битовых манипуляций.");

            Y += 30;
            inn->Height = Y;
        }
        void BuildAtbashTheory() {

            Panel^ scroll = gcnew Panel();
            scroll->Dock = DockStyle::Fill;
            scroll->AutoScroll = true;
            scroll->BackColor = CLR_BG_DARK;

            pnlAtbashTheory->Controls->Add(scroll);

            Panel^ inn = gcnew Panel();
            inn->Location = Point(0, 0);
            inn->Width = 990;
            inn->BackColor = CLR_BG_DARK;

            scroll->Controls->Add(inn);

            int Y = 16;
            int CW = 968;

            // Заголовок
            Panel^ hdr = gcnew Panel();
            hdr->Location = Point(10, Y);
            hdr->Size = System::Drawing::Size(CW, 60);
            hdr->BackColor = CLR_ACCENT;
            inn->Controls->Add(hdr);

            AL(hdr, L"ШИФР АТБАШ", 0, 0, CW, 60,
                gcnew System::Drawing::Font(L"Segoe UI", 18, FontStyle::Bold),
                Color::White, ContentAlignment::MiddleCenter);

            Y += 80;

            // 1. Введение
            Y = SecTitle(inn, Y, CW, L"1. Введение");
            Y = TxtBlk(inn, Y, CW,
                L"Шифр Атбаш — простой метод подстановки, в котором каждая буква заменяется на зеркальную в алфавите "
                L"(первая становится последней, вторая — предпоследней). Он используется как наглядный пример базового принципа шифрования.");
            Y = TxtBlk(inn, Y, CW,
                L"Алгоритм удобен для обучения: он показывает связь между символом, его позицией и результатом преобразования.");

            // 2. История
            Y = SecTitle(inn, Y, CW, L"2. Историческая справка");
            Y = TxtBlk(inn, Y, CW,
                L"Атбаш возник в древнееврейской традиции и является одним из самых ранних подстановочных шифров. "
                L"Он не использует ключ — правило задаётся самим алфавитом.");

            // 3. Теория
            Y = SecTitle(inn, Y, CW, L"3. Теоретические основы");
            Y = TxtBlk(inn, Y, CW,
                L"Атбаш — это моноалфавитная подстановка. Для буквы с индексом i используется формула:");

            Y = FmBox(inn, Y, CW, L"(N - 1) - i");

            Y = TxtBlk(inn, Y, CW,
                L"Где N — размер алфавита (33 для русского, 26 для английского). "
                L"Алгоритм сохраняет регистр и не изменяет небуквенные символы.");

            // 4. Алгоритм
            Y = SecTitle(inn, Y, CW, L"4. Алгоритм");
            Y = NumList(inn, Y, CW, gcnew cli::array<String^> {
                L"Выбрать алфавит (RU/EN)",
                    L"Определить позицию буквы",
                    L"Применить формулу (N-1-i)",
                    L"Получить зеркальную букву",
                    L"Сохранить регистр"
            });

            Y = TxtBlk(inn, Y, CW,
                L"Дешифрование выполняется тем же алгоритмом.");

            // 5. Пример
            Y = SecTitle(inn, Y, CW, L"5. Пример");
            Y = HlBox(inn, Y, CW,
                L"Пример",
                L"КРИПТО → ФРЩПОТ");

            // 6. Применение
            Y = SecTitle(inn, Y, CW, L"6. Применение");
            Y = TxtBlk(inn, Y, CW,
                L"Алгоритм используется в учебных системах для демонстрации принципов криптографии "
                L"и визуализации преобразования текста.");

            // 7. Заключение
            Y = SecTitle(inn, Y, CW, L"7. Заключение");
            Y = TxtBlk(inn, Y, CW,
                L"Атбаш прост в реализации и хорошо подходит для обучения, "
                L"но не обеспечивает реальную криптографическую защиту.");

            inn->Height = Y + 30;
        }

        // =====================================================================
        //  БЛОК ИНФОГРАФИКИ — PNG вставляется по центру с подложкой
        // =====================================================================
    private:
        // filename  — имя PNG-файла рядом с exe
        // imgH      — желаемая высота отображения (ширина масштабируется пропорционально)
        int InfographicBlock(Panel^ parent, int y, int cw, String^ filename, int imgH) {
            // Подложка
            Panel^ card = gcnew Panel();
            card->Location = Point(10, y);
            card->Width = cw;
            card->BackColor = Color::FromArgb(18, 32, 58);
            parent->Controls->Add(card);

            PictureBox^ pb = gcnew PictureBox();
            pb->SizeMode = PictureBoxSizeMode::Zoom;
            pb->BackColor = Color::Transparent;

            // Пробуем загрузить изображение
            Image^ img = LoadInfographic(filename);
            if (img != nullptr) {
                pb->Image = img;
                // Вычисляем ширину пропорционально
                int imgW = (img->Width * imgH) / img->Height;
                if (imgW > cw - 40) { imgW = cw - 40; }
                pb->Size = System::Drawing::Size(imgW, imgH);
                pb->Location = Point((cw - imgW) / 2, 12);
                card->Height = imgH + 24;
            }
            else {
                // Файл не найден — показываем заглушку с именем файла
                pb->Size = System::Drawing::Size(cw - 40, imgH);
                pb->Location = Point(20, 12);
                card->Height = imgH + 24;
                Label^ stub = gcnew Label();
                stub->Text = L"[Изображение: " + filename + L"]\nПоместите файл рядом с exe";
                stub->Dock = DockStyle::Fill;
                stub->TextAlign = ContentAlignment::MiddleCenter;
                stub->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Italic);
                stub->ForeColor = Color::FromArgb(150, 170, 200);
                stub->BackColor = Color::Transparent;
                pb->Controls->Add(stub);
            }

            card->Controls->Add(pb);
            return y + card->Height + 12;
        }

        // =====================================================================
        //  ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ТЕОРИИ
        // =====================================================================
    private:
        int SecTitle(Panel^ p, int y, int cw, String^ t) {
            Panel^ b = gcnew Panel(); b->Location = Point(10, y);
            b->Size = System::Drawing::Size(cw, 4); b->BackColor = CLR_ACCENT; p->Controls->Add(b); y += 8;
            Panel^ c = gcnew Panel(); c->Location = Point(10, y);
            c->Size = System::Drawing::Size(cw, 38); c->BackColor = Color::FromArgb(20, 35, 60); p->Controls->Add(c);
            AL(c, t, 14, 0, cw - 28, 38, gcnew System::Drawing::Font(L"Segoe UI", 12.0f, FontStyle::Bold),
                Color::White, ContentAlignment::MiddleLeft);
            return y + 46;
        }
        int SubTit(Panel^ p, int y, int cw, String^ t) {
            Label^ l = gcnew Label(); l->Text = t; l->Location = Point(10, y);
            l->Size = System::Drawing::Size(cw, 22);
            l->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5f, FontStyle::Bold | FontStyle::Italic);
            l->ForeColor = CLR_ORANGE; l->BackColor = Color::Transparent; l->AutoSize = false;
            p->Controls->Add(l); return y + 26;
        }
        int TxtBlk(Panel^ p, int y, int cw, String^ t) {
            Panel^ c = gcnew Panel(); c->Location = Point(10, y);
            c->Width = cw; c->BackColor = Color::Transparent; p->Controls->Add(c);
            Label^ l = gcnew Label(); l->Text = t; l->Location = Point(8, 6);
            l->Width = cw - 16;
            l->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5f);
            l->ForeColor = Color::FromArgb(220, 230, 245); l->BackColor = Color::Transparent;
            l->AutoSize = false; l->MaximumSize = System::Drawing::Size(cw - 16, 0); l->AutoSize = true;
            c->Controls->Add(l);
            Graphics^ g = p->CreateGraphics();
            System::Drawing::SizeF sz = g->MeasureString(t, gcnew System::Drawing::Font(L"Segoe UI", 9.5f), cw - 16);
            delete g;
            int h = (int)sz.Height + 22; c->Height = h; return y + h + 4;
        }
        int HlBox(Panel^ p, int y, int cw, String^ title, String^ body) {
            Panel^ c = gcnew Panel(); c->Location = Point(10, y); c->Width = cw;
            c->BackColor = Color::FromArgb(22, 50, 90); p->Controls->Add(c);
            Panel^ s = gcnew Panel(); s->Location = Point(0, 0); s->Width = 5;
            s->Dock = DockStyle::Left; s->BackColor = CLR_ORANGE; c->Controls->Add(s);
            Label^ lt = gcnew Label(); lt->Text = title; lt->Location = Point(14, 8); lt->Width = cw - 22;
            lt->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5f, FontStyle::Bold);
            lt->ForeColor = CLR_ORANGE; lt->BackColor = Color::Transparent;
            lt->AutoSize = false; lt->MaximumSize = System::Drawing::Size(cw - 22, 0); lt->AutoSize = true;
            c->Controls->Add(lt);
            Label^ lb = gcnew Label(); lb->Text = body; lb->Location = Point(14, lt->Bottom + 4); lb->Width = cw - 22;
            lb->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);
            lb->ForeColor = Color::FromArgb(200, 215, 235); lb->BackColor = Color::Transparent;
            lb->AutoSize = false; lb->MaximumSize = System::Drawing::Size(cw - 22, 0); lb->AutoSize = true;
            c->Controls->Add(lb);
            c->Height = lb->Bottom + 12; return y + c->Height + 6;
        }
        int NumList(Panel^ p, int y, int cw, cli::array<String^>^ items) {
            Panel^ c = gcnew Panel(); c->Location = Point(10, y); c->Width = cw;
            c->BackColor = Color::Transparent; p->Controls->Add(c);
            int cy = 4;
            for (int i = 0; i < items->Length; i++) {
                Panel^ nb = gcnew Panel(); nb->Location = Point(8, cy);
                nb->Size = System::Drawing::Size(26, 26); nb->BackColor = CLR_ACCENT; c->Controls->Add(nb);
                Label^ nm = gcnew Label(); nm->Text = (i + 1).ToString(); nm->Dock = DockStyle::Fill;
                nm->TextAlign = ContentAlignment::MiddleCenter;
                nm->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Bold);
                nm->ForeColor = Color::White; nm->BackColor = Color::Transparent; nb->Controls->Add(nm);
                Label^ l = gcnew Label(); l->Text = items[i]; l->Location = Point(42, cy); l->Width = cw - 54;
                l->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);
                l->ForeColor = Color::FromArgb(210, 225, 245); l->BackColor = Color::Transparent;
                l->AutoSize = false; l->MaximumSize = System::Drawing::Size(cw - 54, 0); l->AutoSize = true;
                c->Controls->Add(l);
                cy = Math::Max(nb->Bottom, l->Bottom) + 8;
            }
            c->Height = cy + 4; return y + c->Height + 4;
        }
        int FmBox(Panel^ p, int y, int cw, String^ f) {
            Panel^ c = gcnew Panel(); c->Location = Point(10, y);
            c->Size = System::Drawing::Size(cw, 52); c->BackColor = Color::FromArgb(15, 28, 50);
            p->Controls->Add(c);
            c->Paint += gcnew PaintEventHandler(this, &Form1::PaintBorder);
            Label^ l = gcnew Label(); l->Text = f; l->Dock = DockStyle::Fill;
            l->TextAlign = ContentAlignment::MiddleCenter;
            l->Font = gcnew System::Drawing::Font(L"Consolas", 13.0f, FontStyle::Bold);
            l->ForeColor = CLR_ORANGE; l->BackColor = Color::Transparent; c->Controls->Add(l);
            return y + 60;
        }
        System::Void PaintBorder(System::Object^ s, PaintEventArgs^ e) {
            Panel^ p = safe_cast<Panel^>(s);
            Pen^ pen = gcnew Pen(CLR_ACCENT, 2);
            e->Graphics->DrawRectangle(pen, 0, 0, p->Width - 1, p->Height - 1); delete pen;
        }

        // =====================================================================
        //  ПЕРЕКЛЮЧЕНИЕ ПАНЕЛЕЙ
        // =====================================================================
    private:
        System::Void rbCalc_CC(System::Object^ s, System::EventArgs^ e) { if (rbCalc->Checked) ShowCalcPanel(); }
        System::Void rbTheory_CC(System::Object^ s, System::EventArgs^ e) { if (rbTheory->Checked) ShowTheoryPanel(); }
        void ShowCalcPanel() { pnlCalc->Visible = true; pnlTheory->Visible = false; }
        void ShowTheoryPanel() { pnlCalc->Visible = false; pnlTheory->Visible = true; }

        // =====================================================================
        //  ЛОГИКА XOR
        // =====================================================================
    private:
        System::Void OnInput(System::Object^ s, System::EventArgs^ e) {
            String^ inp = txtInput->Text; String^ key = txtKey->Text;
            if (key->Length == 0) { ClearBits(); txtResult->Text = L""; txtHex->Text = L""; txtMass->Text = L""; return; }
            System::Text::StringBuilder^ hx = gcnew System::Text::StringBuilder();
            System::Text::StringBuilder^ ms = gcnew System::Text::StringBuilder();
            ms->Append(L"[");
            for (int i = 0; i < inp->Length; i++) {
                int cc = (int)((wchar_t)(inp[i] ^ key[i % key->Length]));
                hx->AppendFormat(L"\\x{0:X2}", cc);
                if (i > 0) ms->Append(L", "); ms->Append(cc);
            }
            ms->Append(L"]");
            String^ fh = hx->ToString();
            txtResult->Text = (fh->Length > 32) ? (fh->Substring(0, 32) + L"...") : fh;
            txtMass->Text = ms->ToString();
            if (inp->Length == 0) { ClearBits(); txtHex->Text = L""; return; }
            unsigned char bI = (unsigned char)(inp[0] & 0xFF);
            unsigned char bK = (unsigned char)(key[0] & 0xFF);
            unsigned char bR = bI ^ bK;
            RnBits(bitsIn, bI, 0); RnBits(bitsKey, bK, 1); RnBits(bitsRes, bR, 2);
            UpdDesc(bI, bK, bR); txtHex->Text = bR.ToString(L"X2");
        }
        void RnBits(cli::array<Panel^>^ row, unsigned char v, int t) {
            for (int i = 0; i < 8; i++) {
                int b = (v >> (7 - i)) & 1; Color bg;
                if (t == 0) bg = b ? CLR_IN_ON : CLR_OFF;
                else if (t == 1) bg = b ? CLR_KEY_1 : CLR_KEY_0;
                else bg = b ? CLR_RES_ON : CLR_OFF;
                row[i]->BackColor = bg;
                safe_cast<Label^>(row[i]->Controls[0])->Text = b ? L"1" : L"0";
            }
        }
        void UpdDesc(unsigned char bI, unsigned char bK, unsigned char bR) {
            lblDescIn->Text = L"БИТЫ ТЕКСТА\n(" + Bin(bI) + L"):";
            lblDescKey->Text = L"БИТЫ КЛЮЧА\n(" + Bin(bK) + L"):";
            lblDescRes->Text = L"РЕЗУЛЬТАТ\n(" + Bin(bR) + L"):";
        }
        String^ Bin(unsigned char v) { String^ s = L""; for (int i = 7; i >= 0; i--) s += ((v >> i) & 1) ? L"1" : L"0"; return s; }
        void ClearBits() {
            for (int i = 0; i < 8; i++) {
                bitsIn[i]->BackColor = CLR_OFF; bitsKey[i]->BackColor = CLR_OFF; bitsRes[i]->BackColor = CLR_OFF;
                safe_cast<Label^>(bitsIn[i]->Controls[0])->Text = L"0";
                safe_cast<Label^>(bitsKey[i]->Controls[0])->Text = L"0";
                safe_cast<Label^>(bitsRes[i]->Controls[0])->Text = L"0";
            }
            lblDescIn->Text = L"БИТЫ ТЕКСТА\n(00000000):";
            lblDescKey->Text = L"БИТЫ КЛЮЧА\n(00000000):";
            lblDescRes->Text = L"РЕЗУЛЬТАТ\n(00000000):";
        }
        System::Void OnBitLbl(System::Object^ s, System::EventArgs^ e) {
            Label^ l = safe_cast<Label^>(s); Panel^ p = safe_cast<Panel^>(l->Parent);
            for (int i = 0; i < 8; i++) if (bitsRes[i] == p) { OnResBit(p, e); return; }
        }
        System::Void OnResBit(System::Object^ s, System::EventArgs^ e) {
            Panel^ p = safe_cast<Panel^>(s); int idx = -1;
            for (int i = 0; i < 8; i++) if (bitsRes[i] == p) { idx = i; break; } if (idx < 0) return;
            unsigned char cur = RdRes(); cur ^= (unsigned char)(1 << (7 - idx));
            int b = (cur >> (7 - idx)) & 1; p->BackColor = b ? CLR_RES_ON : CLR_OFF;
            safe_cast<Label^>(p->Controls[0])->Text = b ? L"1" : L"0";
            lblDescRes->Text = L"РЕЗУЛЬТАТ\n(" + Bin(cur) + L"):"; txtHex->Text = cur.ToString(L"X2");
        }
        unsigned char RdRes() {
            unsigned char v = 0;
            for (int i = 0; i < 8; i++) if (safe_cast<Label^>(bitsRes[i]->Controls[0])->Text == L"1") v |= (unsigned char)(1 << (7 - i));
            return v;
        }
        System::Void OnReset(System::Object^ s, System::EventArgs^ e) {
            txtInput->Clear(); txtKey->Clear(); txtResult->Clear(); txtHex->Clear(); txtMass->Clear(); ClearBits();
        }
        System::Void OnToggle(System::Object^ s, System::EventArgs^ e) {
            unsigned char cur = (~RdRes()) & 0xFF; RnBits(bitsRes, cur, 2);
            lblDescRes->Text = L"РЕЗУЛЬТАТ\n(" + Bin(cur) + L"):"; txtHex->Text = cur.ToString(L"X2");
        }
        System::Void OnAtbashInput(System::Object^ sender, System::EventArgs^ e) {
            txtAtbashOut->Text = Atbash(txtAtbashIn->Text);
        }
        System::Void OnLangToggle(System::Object^ sender, System::EventArgs^ e) {
            isRussian = !isRussian;

            if (isRussian) {
                btnLang->Text = L"RU";
                btnLang->BackColor = Color::FromArgb(30, 100, 180);
            }
            else {
                btnLang->Text = L"EN";
                btnLang->BackColor = Color::FromArgb(0, 150, 120);
            }

            txtAtbashOut->Text = Atbash(txtAtbashIn->Text);
        }
        System::Void rbAtbashCalc_CC(System::Object^ s, System::EventArgs^ e) {
            if (rbAtbashCalc->Checked) {
                pnlAtbashCalc->Visible = true;
                pnlAtbashTheory->Visible = false;
            }
        }

        System::Void rbAtbashTheory_CC(System::Object^ s, System::EventArgs^ e) {
            if (rbAtbashTheory->Checked) {
                pnlAtbashCalc->Visible = false;
                pnlAtbashTheory->Visible = true;
            }
        }
        System::Void OnAtbashRun(System::Object^ sender, System::EventArgs^ e)
        {
            txtAtbashOut->Text = Atbash(txtAtbashIn->Text);
        }
        
    };
}