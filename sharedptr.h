#pragma once

//SharedPtr

//Кроме хранения указателя на объект,SharedPtr хранит еще и счетчик ссылок (количество объектов SharedPtr, которые хранят один и тот же указатель).
//Имея такой счетчик, мы можем определить момент, когда на объект, выделенный в куче, не останется больше ссылок(когда счетчик ссылок станет равным 0), и освободить память.
//Переменную-счетчик будем хранить в динамичекой памяти, чтобы у всех объектов SharedPtr было одно и то же значение их количества

template <typename T>
struct SharedPtr {
	explicit SharedPtr(T* ptr = 0) :ptr_(ptr) {  //Конструктор, принимающий указатель 
		if (ptr_ != 0)
			count_ = new int(1);//Создадим счетчик ссылок в динам. памяти. Если указатель ненулевой, инициализируем count единицей, в противном случае нулем
		else
			count_ = new int(0);
	}

	SharedPtr(SharedPtr const& sp) :ptr_(sp.ptr_), count_(sp.count_) {  //Конструктор копирования 
		if (*count_ != 0)
			(*count_)++;
	}

	SharedPtr& operator=(SharedPtr const& sp) {
		if (this != &sp)
		{
			if (ptr_ != 0)//если текущий указатель указывает на существующий объект, требуется декрементировать счетчик ссылок и при необходимости освободить память 
			{
				(*count_)--;

				if (*count_ == 0)
				{
					delete ptr_;
					delete count_;
				}

				ptr_ = sp.ptr_; //присываиваем новые значения 
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

	T* get()const { //возвращает указатель, сохраненный внутри SharedPtr
		return this->ptr_;
	}

	void reset(T* ptr = 0) { //метод освобождает старый указатель и захватывает новый 
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

	T& operator*()const {  //получение значения, на кот. указывает ук-ль 
		return *this->ptr_;
	}
	T* operator->()const { //получение самого указателя 
		return this->ptr_;
	}


private:
	T* ptr_;
	int* count_;
};

