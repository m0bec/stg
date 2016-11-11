

#include "DxLib.h"
#include "control.h"

// WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(FALSE);
	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(1280, 1024, 16);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1) return -1;

	control &main_run = control::getinstance();

	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	main_run.firstrun();
	// �ړ����[�`��
	while (1)
	{
		// ��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		main_run.run();
		if (CheckHitKey(KEY_INPUT_P) == 1) {
			SaveDrawScreen(0, 0, 1280, 1024, "Save.bmp");
		}
		// ����ʂ̓��e��\��ʂɃR�s�[����
		ScreenFlip();
		

		// Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
		// -1 ���Ԃ��Ă����烋�[�v�𔲂���
		if (ProcessMessage() < 0) break;

		// �����d�r�b�L�[��������Ă����烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
		if (main_run.pass_state() == 99) break;
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;					// �\�t�g�̏I��
}

