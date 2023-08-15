#include "stdafx.h"
#include "ShaderManager.h"
#include "Objects.h"


int t = 0;
int dt = 1; //시간이 증가하는 양

float obs_bb_x = 0.15f;
float body_bb_x = 0;

random_device rng;
uniform_real_distribution<float>uid(-0.5f, 0.5f);
uniform_real_distribution<float>uid_t(-100.f, -30.0f);

//snow
uniform_real_distribution<float>uid_snow_x(-0.5f, 0.5f);
uniform_real_distribution<float>uid_snow_y(0.8f, 1.0f);
uniform_real_distribution<float>uid_snow_z(-100.f, 100.0f);

//ring_obs
uniform_real_distribution<float>uid_ring(-0.25f, 0.25f);

default_random_engine dre(rng());

uniform_int_distribution<>uid2(0, 2);
default_random_engine dre2(rng());


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void KeyPressed(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void Timerfunction(int value);

enum Camera { first_p_view, third_p_view };
Camera d = third_p_view;

enum State {in_game_state, game_over_state};
State state = in_game_state;



vector<Obstacle> obs;
vector<RingObstacle> ring_obs;
vector<OC_Obstacle> oc_obs;

vector<Tree> trees;
vector<Snow> snow;
Ground ground;
Player player;
Objects objs;

// UI
GameOver_UI gameover_ui;
Score_UI score_ui;

int main(int argc, char** argv) // 윈도우 출력하고 콜백함수 설정 
{
	//--- 윈도우 생성하기 
	glutInit(&argc, argv); // glut 초기화 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(0, 0); // 윈도우의 위치 지정 
	glutInitWindowSize(1000, 800); // 윈도우의 크기 지정 
	glutCreateWindow("TermProject_2017180012_jypark"); // 윈도우 생성 (윈도우 이름) 

	//--- GLEW 초기화하기 
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화 
	{
		cerr << "Unable to initialize GLEW" << endl;
		exit(EXIT_FAILURE);
	}
	else
		cout << "GLEW Initialized\n";

	ShaderManager::Inst()->Init();
	objs.Init();

	//-----------------------------------------------------------
	glEnable(GL_DEPTH_TEST);

	glutTimerFunc(10, Timerfunction, 1); //애니메이션

	//키보드
	glutKeyboardFunc(KeyPressed);
	glutKeyboardUpFunc(KeyUp);
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정

	glutMainLoop(); // 이벤트 처리 시작 
}

float middle_angle_x = 0.f;

float top_angle_z = 0.f;

float camera_pos_z = 7.0f;
float camera_pos_x = -1.0f;

float camera_dir_x = 0.0f;

float the = 0;
float new_the = 0;


// 카메라 //
//3인칭
float c_pos_x = 0.0f;
float c_pos_y = 0.5f;
float c_pos_z = 0.0f;

//1인칭
float c_pos_x_f = player.GetX();
float c_pos_y_f = player.GetY();
float c_pos_z_f = -player.GetZ() - 0.5f;

float c_pos_dx_f = 0.0f;
float c_pos_dy_f = 0.0f;
float c_pos_dz_f = 0.0f;
//-------------------

float gravity = -0.01f;
float friction = -0.12f;
float player_acc = 0.05f;

float acc_x = 0.0f;
float acc_y = gravity;

int r_pressed = 0;
GLboolean p_pressed = false;
GLboolean snowing = false;

void KeyPressed(unsigned char key, int x, int y) {
	switch (key) {
	case VK_ESCAPE:
		glutLeaveMainLoop();
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	case 'w':
		player.SetDZ(-0.05f);
		c_pos_dz_f = -0.05f;
		break;
	case 'a':
		player.SetDX(-0.05f);
		c_pos_dx_f = -0.05f;

		break;
	case 's':
		player.SetDZ(0.05f);
		c_pos_dz_f = 0.05f;
		break;
	case 'd':
		player.SetDX(0.05f);
		c_pos_dx_f = 0.05f;
		break;
	case VK_SPACE: //점프
		if (player.GetY() == 0)
			player.SetDY(0.15f);
		break;
	case 'r':
		if (state == game_over_state)
		{
			state = in_game_state;

			player.SetAngle(0.f);
			middle_angle_x = 0.f;
			top_angle_z = 0.f;

			camera_pos_z = 7.0f;
			camera_pos_x = -1.0f;

			camera_dir_x = 0.0f;

			the = 0;
			new_the = 0;

			light_x = 1.2f;
			light_y = 1.0f;
			light_z = 2.0f;

			c_pos_x = 0.0f;
			c_pos_y = 0.5f;
			c_pos_z = 0.0f;

			c_pos_x_f = player.GetX();
			c_pos_y_f = player.GetY();
			c_pos_z_f = -player.GetZ() - 0.5f;

			c_pos_dx_f = 0.0f;
			c_pos_dy_f = 0.0f;
			c_pos_dz_f = 0.0f;
			//---------------
			player.SetPos(0, 0, 0);
			player.SetVelocity(0.f, 0.f, 0.f);
			player.IsJumping = false;
			player.SetLkeyPressCount(0);

			gravity = -0.01f;
			friction = -0.12f;
			player_acc = 0.05f;

			acc_x = 0.0f;
			acc_y = gravity;

			r_pressed = 0;
			p_pressed = false;

			state = in_game_state;
			d = third_p_view;

			score_ui.SetLife(10);

			t = 0;

			//dis_l = 0;
			//dis_r = 0;
			//dis_oc_lr = 0;
			//dis_oc_rl = 0;

			score_ui.SetScore(0);

			body_bb_x = 0;
		}
		r_pressed++;
		break;

	case 'l':
		if (player.GetLkeyPressCount() > 10)
			player.IsLkeyPressed = false;
		else 
			player.IsLkeyPressed = true;

		break;
	case '1': //1인칭 시접으로 변경
		d = first_p_view;
		break;
	case '3':
		d = third_p_view;
		break;
	case 'u':
		score_ui.DecreaseLife();
		break;
	}

	glutPostRedisplay();
}

void KeyUp(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 'w':
		if (snowing == false)
		{
			player.SetDZ(0.f);
			c_pos_dz_f = 0.0f;
		}
		break;
	case 'a':
		if (snowing == false)
		{
			player.SetDX(0.f);
			c_pos_dx_f = 0.0f;
		}
		break;
	case 's':
		if (snowing == false)
		{
			player.SetDZ(0.f);
			c_pos_dz_f = 0.0f;
		}
		break;
	case 'd':
		if (snowing == false)
		{
			player.SetDX(0.f);
			c_pos_dx_f = 0.0f;
		}
		break;
	case 'l':
		player.IncreaseLkeyPressCount();
		player.IsLkeyPressed = false;
		break;
	case VK_SPACE: //점프
		player.IsJumping = true;
		break;
	}
	glutPostRedisplay();

}

GLvoid drawScene() // 콜백 함수: 출력 
{
	if (state == in_game_state)
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLuint shader = ShaderManager::Inst()->GetShaderProgram();
		glUseProgram(shader);

		if (d == third_p_view)
		{
			//공용 카메라------------------------
			glm::vec3 cameraPos = glm::vec3(0.0f, c_pos_y, 7.0f);
			glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::mat4 view = glm::mat4(1.0f);
			view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

			unsigned int viewLocation = glGetUniformLocation(shader, "viewTransform");
			glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
		}
		if (d == first_p_view) 
		{
			if (player.IsLkeyPressed == true) {
				//공용 카메라------------------------
				glm::vec3 cameraPos = glm::vec3(c_pos_x_f, player.GetY() - 0.25f, c_pos_z_f);
				glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, -50.0f);
				glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
				glm::mat4 view = glm::mat4(1.0f);
				view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

				unsigned int viewLocation = glGetUniformLocation(shader, "viewTransform");
				glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
			}
			else {
				//공용 카메라------------------------
				glm::vec3 cameraPos = glm::vec3(c_pos_x_f, player.GetY(), c_pos_z_f);
				glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, -50.0f);
				glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
				glm::mat4 view = glm::mat4(1.0f);
				view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

				unsigned int viewLocation = glGetUniformLocation(shader, "viewTransform");
				glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
			}

		}

		//공용 투영
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(30.0f), (float)800 / (float)800, 0.1f, 100.0f);

		unsigned int projectionLocation = glGetUniformLocation(shader, "projectionTransform");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
		//-----------------------------------

		//땅바닥
		ground.Draw();

		//player---------------------------------------------------------
		player.Draw();

		//장애물들 생성-------------------------------------------------------
		for (auto obs_iter = obs.begin(); obs_iter != obs.end(); ++obs_iter)
			obs_iter->Draw();

		for (auto ring_iter = ring_obs.begin(); ring_iter != ring_obs.end(); ++ring_iter)
			ring_iter->Draw();

		for (auto oc_iter = oc_obs.begin(); oc_iter != oc_obs.end(); ++oc_iter)
			oc_iter->Draw();

		//tree
		for (auto tree_iter = trees.begin(); tree_iter != trees.end(); ++tree_iter)
			tree_iter->Draw();

		//snow
		for (auto sn_iter = snow.begin(); sn_iter != snow.end(); ++sn_iter)
			sn_iter->Draw();

		//UI
		//----------------------------------------------
		score_ui.Draw();
	}	
	else if (state == game_over_state) //게임 오버 창
	{
		gameover_ui.Draw();
	}
	
	//그리기
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h) // 콜백 함수: 다시 그리기 
{
	glViewport(0, 0, w, h);
}

void Timerfunction(int value)
{
	if (score_ui.GetLife() <= 0)
	{
		state = game_over_state;
	}

	if (player.IsLkeyPressed)
	{
		body_bb_x = 0.15f;
	}
	else 
	{
		body_bb_x = 0.25f;
	}

	//-----------------------------------
	//플레이어 움직임
	player.MovePos(player.GetDX() * dt, player.GetDY() * dt, player.GetDZ() * dt);
	player.MoveDY(gravity);

	//-----------------------------------
	//1인칭 카메라 움직임
	c_pos_x_f += c_pos_dx_f;
	c_pos_y_f += c_pos_dy_f;
	c_pos_z_f += c_pos_dz_f;

	c_pos_dy_f += gravity;
	//-------------------------------------

	//플레이어&바닥 충돌처리
	if (player.GetY() <= 0.f)
	{
		player.SetY(0.f);
		player.IsJumping = false;
	}
	if (player.GetX() < -0.7f)
		player.SetX(-0.7f);
	else if (player.GetX() >= 0.7f)
		player.SetX(0.7f);

	//카메라 충돌처리
	if (c_pos_y_f <= -0.f)
	{
		c_pos_y_f = -0.f;
		player.IsJumping = false;
	}

	if (c_pos_x_f <= -0.7f)
	{
		c_pos_x_f = -0.7f;
	}
	else if (c_pos_x_f >= 0.7f) 
	{
		c_pos_x_f = 0.7f;
	}

	//기본 장애물
	for (auto obs_iter = obs.begin(); obs_iter != obs.end();)
	{
		float dis_l = sqrt(pow(((player.GetX() - body_bb_x) - obs_iter->GetX() + obs_bb_x), 2) + pow(((player.GetY()) - obs_iter->GetY()), 2)
			+ pow(((player.GetZ() - body_bb_x) - obs_iter->GetZ() + obs_bb_x), 2));
		float dis_r = sqrt(pow(((player.GetX() + body_bb_x) - obs_iter->GetX() - obs_bb_x), 2) + pow(((player.GetY())-obs_iter->GetY()), 2)
			+ pow(((player.GetZ() - body_bb_x) - obs_iter->GetZ() + obs_bb_x), 2));


		if (dis_l <= 0.4f || dis_r <=0.4f) 
		{
			//cout << "충돌!" << endl;
			score_ui.DecreaseLife();
			obs_iter = obs.erase(obs_iter);

			if (score_ui.GetLife() < 0)
				score_ui.SetLife(0.f);
		}
		
		if (obs_iter->Update() || score_ui.GetLife() <= 0)
		{
			obs_iter = obs.erase(obs_iter);
			//cout << "삭제" << endl;
		}
		else 
			++obs_iter;
	}

	for (auto ring_iter = ring_obs.begin(); ring_iter != ring_obs.end();)
	{
		if (ring_iter->Update() || score_ui.GetLife() <= 0)
		{
			ring_iter = ring_obs.erase(ring_iter);
		}
		else
		{
			++ring_iter;
		}
	}

	//왼&오
	for (auto oc_iter = oc_obs.begin(); oc_iter != oc_obs.end();)
	{
		float dis_oc_lr = sqrt(pow(((player.GetX() - body_bb_x) - oc_iter->GetX_L() + obs_bb_x), 2) + pow(((player.GetY())-oc_iter->GetX_L()), 2)
			+ pow(((player.GetZ() - body_bb_x) - oc_iter->GetZ_L() + obs_bb_x), 2));
		float dis_oc_rl = sqrt(pow(((player.GetX() + body_bb_x) - oc_iter->GetX_R() - obs_bb_x), 2) + pow(((player.GetY())-oc_iter->GetY_R()), 2)
			+ pow(((player.GetZ() - body_bb_x) - oc_iter->GetZ_R() + obs_bb_x), 2));

		if (dis_oc_lr <= 0.4f || dis_oc_rl <= 0.4f) 
		{
			//cout << "충돌!oc" << endl;
			score_ui.DecreaseLife();
			oc_iter = oc_obs.erase(oc_iter);

			if (score_ui.GetLife() < 0)
				score_ui.SetLife(0.f);
		}

		if (oc_iter->Update() || score_ui.GetLife() <= 0)
			oc_iter = oc_obs.erase(oc_iter);
		else
			++oc_iter;
	}


	for (auto tree_iter = trees.begin(); tree_iter != trees.end();) 
	{
		if (tree_iter->Update() || score_ui.GetLife() <= 0)
			tree_iter = trees.erase(tree_iter);
		else 
			++tree_iter;
	}

	t += dt; //시간이 지남에 따라 장애물이 다가온다.

	if (t % 20 == 0)
	{
		trees.emplace_back(1.15f, -50.0f); //right side trees
		trees.emplace_back(-1.15f, -50.0f); //left side trees
	}
	if (t % 50 == 0) 
	{
		obs.emplace_back(uid(dre), -0.25f, -50.0f);
	}
	if (t % 160 == 0)
	{
		ring_obs.emplace_back(uid(dre), uid_ring(dre), -50.0f);
	}
	if (t % 270 == 0)
	{
		oc_obs.emplace_back(-0.6f, -0.25f, -50.0f, 0.6f, -0.25f, -50.0f);
	}

	//snow
	snow.emplace_back(uid_snow_x(dre), uid_snow_y(dre), uid_snow_z(dre));

	if ((t > 1000 && t < 1500) || (t > 3000 && t < 3500) || (t > 5000 && t < 5500) || (t > 6000 && t < 6500) || (t > 7000 && t < 7500) || (t > 8000 && t < 8500) || (t > 9000 && t < 9500)
		|| (t > 10000 && t < 10500) || (t > 12000 && t < 12500) || (t > 13000 && t < 13500) || (t > 14000 && t < 14500) || (t > 15000 && t < 15500) || (t > 17000 && t < 17500) 
		|| (t > 18000 && t < 18500) || (t > 19000 && t < 20000)) 
	{
		snowing = true;

		//땅
		ground.SetColor(1.0f, 0.8f, 0.6f);

		//나무
		for (auto& tree : trees)
		{
			tree.SetColor(0.7f, 1.0f, 0.7f);
		}

		for (auto sn_iter = snow.begin(); sn_iter != snow.end();)
		{
			if (sn_iter->Update() || score_ui.GetLife() <= 0)
			{
				sn_iter = snow.erase(sn_iter);
			}
			else 
			{
				++sn_iter;
			}
		}
	}
	else 
	{
		snowing = false;
		//땅
		ground.SetColor(1.0f, 0.5f, 0.3f);

		//나무
		for (auto& tree : trees)
		{
			tree.SetColor(0.0f, 0.8f, 0.0f);
		}
		for (auto sn_iter = snow.begin(); sn_iter != snow.end(); ) 
		{
			sn_iter = snow.erase(sn_iter);
		}
	}

	if (r_pressed % 2 == 1) 
	{
		the += 1;
		new_the = (float)(the + 65)*(3.14 / 180);
		light_x = 5.0 * cos(new_the);
		light_y = 5.0 * sin(new_the);
	}
	if (r_pressed % 2 == 0) {
		the -= 1;
		new_the = (float)(the + 65)*(3.14 / 180);
		light_x = 5.0 * cos(new_the);
		light_y = 5.0 * sin(new_the);
	}

	glutPostRedisplay();
	glutTimerFunc(10, Timerfunction, 1);
}