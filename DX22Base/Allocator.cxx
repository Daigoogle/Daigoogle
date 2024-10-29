#include "Allocator.hxx"
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include <sstream>

//#include "Defines.hxx"
#include "ddd_sdl.hxx"

namespace {
	/// @brief �^���̃f�[�^�Ǘ��E�\�[�g�p
	struct putt {
		size_t GetSize() { return size; }
		std::string type = {};
		size_t size = 0;
	};

	/// @brief �|�C���^���̏����L�^����\����
	struct ReakCheck {
		size_t size;// �������T�C�Y
		unsigned short TypeTag;// �^�̃^�O
		unsigned short FileTag;// �t�@�C���̃^�O
		unsigned short Line;// �s��
	};

	/// @brief �|�C���^���̏����L�^����}�b�v�̃|�C���^
	/// @brief �N���X�Œ��ɒ�`����ƁA�������̊֌W�Ńf�X�g���N�^���ɃG���[���o�邽�߃|�C���^�Ŏ��B
	std::map<void*, ReakCheck>* ReakMap;

	/// @brief ���������[�N��f�[�^�ʂȂǂ̏����Ǘ�����N���X
	struct ___reak 
	{ 
		___reak() { ReakMap = &ReakMapOlg; }
		~___reak() 
		{
			std::cout << "--------------------- ���[�N�ꗗ ------------------------" << std::endl;
			for (auto& elem : ReakMapOlg)
			{
				std::cout << TypeNames[elem.second.TypeTag] << "::" <<
					elem.second.size << "byte at File:" <<
					FileNames[elem.second.FileTag] << " To Line:" <<
					elem.second.Line << std::endl;
			}
			rewind(stdin); (void)getchar();
			ReakMap = nullptr;
		}
		size_t usingMemorySize = 0; // �g�p���̃���������
		std::map <std::string, size_t > memMap; // �^���������g�p�ʂ̊i�[��
		std::vector<std::string> FileNames = { "UnKnown" }; // �t�@�C�����̊i�[��
		std::vector<std::string> TypeNames = { "UnKnown" }; // �^���̊i�[��
		std::map<void*, ReakCheck> ReakMapOlg; // �|�C���^���̏����i�[����}�b�v
	};

	/// @brief ���������[�N�E�f�[�^�Ǘ��\���̂̃C���X�^���X
	/// @brief �������Ǘ��N���X���O���[�o���Ŏ����Ƃɂ��A�f�X�g���N�^�Ń��[�N����\������B
	___reak reak;
	
}

/// @brief ���������[�N�̏��𐮗����ĕԂ�
/// @param size �f�[�^�T�C�Y
/// @param type �f�[�^�^
/// @param FileName �t�@�C����
/// @param Line �s��
/// @return �|�C���^�Ɋ֘A�Â�����
ReakCheck MakeReakCheckParam(size_t size, const type_info& type, const std::string& FileName, int Line)
{
	reak.usingMemorySize += size;
	ReakCheck c;

	std::istringstream sst(FileName);
	std::string file;
	// �t�@�C���p�X����t�@�C�����������擾
	while (std::getline(sst, file, '\\'));

	addMemorySize(type.name(), size);
	reak.memMap[type.name()] += size;

	c.size = size;
	c.Line = Line;

	/// �������Ė�����Βǉ�
	bool sucsess = false;
	for (size_t i = 0; i < reak.FileNames.size(); i++) {
		if (reak.FileNames[i] == file) {
			c.FileTag = i;
			sucsess = true;
			break;
		}
	}
	if (!sucsess) {
		c.FileTag = reak.FileNames.size();
		reak.FileNames.push_back(file);
	}

	sucsess = false;

	file = type.name();

	/// �������Ė�����Βǉ�
	for (size_t i = 0; i < reak.TypeNames.size(); i++) {
		if (reak.TypeNames[i] == file) {
			c.TypeTag = i;
			sucsess = true;
			break;
		}
	}
	if (!sucsess) {
		c.TypeTag = reak.TypeNames.size();
		reak.TypeNames.push_back(file);
	}

	return c;
}

void* operator new(size_t size, const type_info& type,const std::string& FileName, int Line)
{	
	void* p = malloc(size);
	(*ReakMap)[p] = MakeReakCheckParam(size,type,FileName,Line);
	return p;
}
void* operator new[](size_t size, const type_info& type, const std::string& FileName, int Line)
{
	void* p = malloc(size);
	(*ReakMap)[p] = MakeReakCheckParam(size, type, FileName, Line);
	return p;
}


void* operator new(size_t size)
{
	reak.usingMemorySize += size;
	return malloc(size);
}
void* operator new[](size_t size)
{
	reak.usingMemorySize += size;
	return malloc(size);
}
//void operator delete(void* p) noexcept
//{
//	if (ReakMap && ReakMap->contains(p))
//		ReakMap->erase(p);
//	free(p);
//}
void operator delete(void* p, size_t size) noexcept
{
	reak.usingMemorySize -= size;
	if(ReakMap && ReakMap->contains(p))
		ReakMap->erase(p);
	free(p);
}

/// @brief �������Ǘ��̂��߂̊֐��@�^���̃f�[�^�ʂ��L�^���܂��B
/// @param type �^��
/// @param size Byte��
void addMemorySize(const std::string& type,size_t size)
{
	reak.memMap[type] += size;
	reak.usingMemorySize += size;
}

/// @brief �������Ǘ��̂��߂̊֐��@�^���̃f�[�^�ʂ��L�^���܂��B
/// @param type �^��
/// @param size Byte��
void deleteMemorySize(const std::string& type, size_t size)
{
	reak.memMap[type] -= size;
	reak.usingMemorySize -= size;
}

/// @brief �^���̃������g�p�ʂ�\�����܂��B
void ShowUsingMemorySize()
{	
	// �x�N�^�[�z��Ɋi�[
	ddd::ExVector<putt> v;
	for (auto& elem : reak.memMap)
		v.push_back({ elem.first, elem.second });

	v.Sort(&putt::GetSize);

	// �\��
	std::cout << std::endl << "�������g�p�ʁF" << reak.usingMemorySize << std::endl << "����{" << std::endl;
	for (auto& elem : v) 
	{
		if(elem.size)
			std::cout << "  " << elem.type << std::endl << "    �� �����F" <<(100 * elem.size) / (float)reak.usingMemorySize << "��  ���v :" << std::setw(4) << elem.size << "byte" << std::endl;
	}
	std::cout << "};" << std::endl;
}