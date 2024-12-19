#pragma once

#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			   System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			   System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			   System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			   this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // chart1
			   // 
			   chartArea1->Name = L"ChartArea1";
			   this->chart1->ChartAreas->Add(chartArea1);
			   legend1->Name = L"Legend1";
			   this->chart1->Legends->Add(legend1);
			   this->chart1->Location = System::Drawing::Point(223, 47);
			   this->chart1->Name = L"chart1";
			   series1->ChartArea = L"ChartArea1";
			   series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			   series1->Legend = L"Legend1";
			   series1->Name = L"QuickSort";
			   series2->ChartArea = L"ChartArea1";
			   series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			   series2->Legend = L"Legend1";
			   series2->Name = L"SelectionSort";
			   this->chart1->Series->Add(series1);
			   this->chart1->Series->Add(series2);
			   this->chart1->Size = System::Drawing::Size(795, 505);
			   this->chart1->TabIndex = 0;
			   this->chart1->Text = L"chart1";
			   // 
			   // button1
			   // 
			   this->button1->Location = System::Drawing::Point(12, 12);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(75, 23);
			   this->button1->TabIndex = 1;
			   this->button1->Text = L"Start";
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			   // 
			   // textBox1
			   // 
			   this->textBox1->Location = System::Drawing::Point(12, 78);
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(180, 22);
			   this->textBox1->TabIndex = 2;
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(12, 59);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(176, 16);
			   this->label1->TabIndex = 3;
			   this->label1->Text = L"Кол-во эл для сортировки";
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1030, 564);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->textBox1);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->chart1);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion

		   void quickSort(std::vector<int>& arr, int low, int high) {
			   if (low < high) {
				   int pi = partition(arr, low, high);
				   quickSort(arr, low, pi - 1);
				   quickSort(arr, pi + 1, high);
			   }
		   }

		   int partition(std::vector<int>& arr, int low, int high) {
			   int pivot = arr[high];
			   int i = low - 1;

			   for (int j = low; j <= high - 1; j++) {
				   if (arr[j] < pivot) {
					   i++;
					   std::swap(arr[i], arr[j]);
				   }
			   }
			   std::swap(arr[i + 1], arr[high]);
			   return i + 1;
		   }

		   void selectionSort(std::vector<int>& arr) {
			   int n = arr.size();
			   for (int i = 0; i < n - 1; i++) {
				   int minIdx = i;
				   for (int j = i + 1; j < n; j++) {
					   if (arr[j] < arr[minIdx])
						   minIdx = j;
				   }
				   std::swap(arr[i], arr[minIdx]);
			   }
		   }

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		this->chart1->Series["QuickSort"]->Points->Clear();
		this->chart1->Series["SelectionSort"]->Points->Clear();

		std::vector<int> arr;
		int n = Convert::ToInt32(this->textBox1->Text);
		for (int i = 0; i < n; ++i) {
			arr.push_back(rand() % 1000);
		}

		std::vector<int> arrQuick = arr;
		std::vector<int> arrSelection = arr;

		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < n; i++) {
			quickSort(arrQuick, 0, i);
			if (i % 100 == 0) {
				auto end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> elapsed = end - start;
				this->chart1->Series["QuickSort"]->Points->AddXY(i, elapsed.count());
			}
		}

		auto start2 = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < n; i++) {
			selectionSort(arrSelection);
			if (i % 100 == 0) {
				auto end2 = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> elapsed2 = end2 - start2;
				this->chart1->Series["SelectionSort"]->Points->AddXY(i, elapsed2.count());
			}
		}
	}
	};
}