#pragma once

//SharedPtr

//����� �������� ��������� �� ������,SharedPtr ������ ��� � ������� ������ (���������� �������� SharedPtr, ������� ������ ���� � ��� �� ���������).
//���� ����� �������, �� ����� ���������� ������, ����� �� ������, ���������� � ����, �� ��������� ������ ������(����� ������� ������ ������ ������ 0), � ���������� ������.
//����������-������� ����� ������� � ����������� ������, ����� � ���� �������� SharedPtr ���� ���� � �� �� �������� �� ����������

template <typename T>
struct SharedPtr {
	explicit SharedPtr(T* ptr = 0) :ptr_(ptr) {  //�����������, ����������� ��������� 
		if (ptr_ != 0)
			count_ = new int(1);//�������� ������� ������ � �����. ������. ���� ��������� ���������, �������������� count ��������, � ��������� ������ �����
		else
			count_ = new int(0);
	}

	SharedPtr(SharedPtr const& sp) :ptr_(sp.ptr_), count_(sp.count_) {  //����������� ����������� 
		if (*count_ != 0)
			(*count_)++;
	}

	SharedPtr& operator=(SharedPtr const& sp) {
		if (this != &sp)
		{
			if (ptr_ != 0)//���� ������� ��������� ��������� �� ������������ ������, ��������� ���������������� ������� ������ � ��� ������������� ���������� ������ 
			{
				(*count_)--;

				if (*count_ == 0)
				{
					delete ptr_;
					delete count_;
				}

				ptr_ = sp.ptr_; //������������ ����� �������� 
				count_ = sp.count_;
				if (*count_)
					(*count_)++;
			}
			else if (ptr_ == 0)
			{
				delete count_;
				ptr_ = sp.ptr_;
				count_ = sp.count_;
				if (*count_)
					(*count_)++;
			}
			return *this;
		}
		else
			return *this;
	}

	~SharedPtr() {
		if (ptr_ != 0 && *count_ > 1) {
			(*count_)--;
		}
		else if (ptr_ != 0 && *count_ == 1)
		{
			(*count_)--;
			delete ptr_;
			delete count_;
		}
		else if (*count_ == 0)
		{
			delete count_;
		}
	}

	T* get()const { //���������� ���������, ����������� ������ SharedPtr
		return this->ptr_;
	}

	void reset(T* ptr = 0) { //����� ����������� ������ ��������� � ����������� ����� 
		if (*count_ != 0)
		{
			(*count_)--;
			if (*count_ == 0)
			{
				delete ptr_;
				delete count_;
			}
		}
		else
			delete count_;

		ptr_ = ptr;
		count_ = new int(0);
		if (ptr_ != 0)
		{
			(*count_)++;
		}
	}
	unsigned int use_count() {
		return *this->count_;
	}

	T& operator*()const {  //��������� ��������, �� ���. ��������� ��-�� 
		return *this->ptr_;
	}
	T* operator->()const { //��������� ������ ��������� 
		return this->ptr_;
	}


private:
	T* ptr_;
	int* count_;
};

