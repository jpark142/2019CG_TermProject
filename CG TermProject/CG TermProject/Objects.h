#pragma once

extern float light_x;
extern float light_y;
extern float light_z;

class Objects
{
public:
	Objects() = default;
	virtual ~Objects() = default;

	void Init();

	void SetVertexData(GLuint& vao, GLuint& vbo, GLsizeiptr size, const GLfloat* data);

	virtual bool Update();
	virtual void Draw();

	void initTexture(const char* imgStr, GLuint& textureID);

protected:
	/*GLuint light_vao, light_vbo;*/
	static GLuint cube_vao, cube_vbo;
	static GLuint game_over_vao, game_over_vbo, game_over_ebo;
	static GLuint ground_vao, ground_vbo;
	static GLuint obs_vao[3], obs_vbo[3];
	static GLuint tree_vao, tree_vbo;

	static GLuint texture1, texture_end;
};

class Player : public Objects
{
public:
	Player() = default;
	~Player() = default;

	void Draw() override;

	float player_bb() {
		return body_x - 0.25f, body_y - 0.25f, body_z - 0.25f,
			body_x + 0.25f, body_y + 0.25f, body_z + 0.25f;
	}

	float GetX() { return body_x; }
	float GetY() { return body_y; }
	float GetZ() { return body_z; }
	void SetPos(float x, float y, float z) {
		body_x = x; body_y = y; body_z = z;
	}
	void SetX(float x) {
		body_x = x;
	}
	void SetY(float y) {
		body_y = y;
	}
	void MovePos(float dx, float dy, float dz) {
		body_x += dx; body_y += dy; body_z += dz;
	}

	float GetDX() { return body_dx; }
	float GetDY() { return body_dy; }
	float GetDZ() { return body_dz; }
	void SetVelocity(float dx, float dy, float dz) {
		body_dx = dx; body_dy = dy; body_dz = dz;
	}
	void SetDX(float dx) {
		body_dx = dx;
	}
	void SetDY(float dy) {
		body_dy = dy;
	}
	void SetDZ(float dz) {
		body_dz = dz;
	}
	void MoveDY(float dy) {
		body_dy += dy;
	}

	void SetAngle(float angle) { player_angle = angle; }

	int GetLkeyPressCount() { return l_pressed_count; }
	void SetLkeyPressCount(int count) { l_pressed_count = count; }
	void IncreaseLkeyPressCount() { l_pressed_count++; }

private:
	float body_x = 0.f;
	float body_y = 0.f;
	float body_z = 0.f;
	float body_dx = 0.0f;
	float body_dy = 0.0f;
	float body_dz = 0.0f;

	float player_angle = 0.f;
	int l_pressed_count = 0;

public:
	bool IsJumping = false;
	bool IsLkeyPressed = false;

};

//-- 장애물들
// Default
class Obstacle : public Objects
{
public:
	Obstacle(float x, float y, float z) :m_x{ x }, m_y{ y }, m_z{ z } {};
	virtual ~Obstacle() = default;

	float GetX() { return m_x; }
	float GetY() { return m_y; }
	float GetZ() { return m_z; }

	float GetBoundingBox() {
		return m_x - 0.15f, m_y - 0.15f, m_z - 0.15f,
			m_x + 0.15f, m_y + 0.15f, m_z + 0.15f;
	}

	bool Update() override;
	void Draw() override;

	//void SetDistanceL(float l_dis) { dis_l = l_dis; }
	//void SetDistanceR(float r_dis) { dis_r = r_dis; }

private:
	float m_x, m_y, m_z;
	//float dis_l = 0;
	//float dis_r = 0;
};

// Open & Close
class OC_Obstacle : public Objects
{
public:
	OC_Obstacle(float xl, float yl, float zl, float xr, float yr, float zr)
		: oc_x{ xl }, oc_y{ yl }, oc_z{ zl }, oc_x2{ xr }, oc_y2{ yr }, oc_z2{ zr } {};

	bool Update() override;
	void Draw() override;

	float GetX_L() { return oc_x; }
	float GetY_L() { return oc_y; }
	float GetZ_L() { return oc_z; }
	float GetX_R() { return oc_x2; }
	float GetY_R() { return oc_y2; }
	float GetZ_R() { return oc_z2; }

private:
	float oc_x, oc_y, oc_z = 0;
	float oc_x2, oc_y2, oc_z2 = 0;

	float oc_dx = 0.01f;
	float oc_dx2 = -0.01f;
};

class RingObstacle : public Objects
{
public:
	RingObstacle(float x, float y, float z) : ring_x{ x }, ring_y{ y }, ring_z{ z } {}

	bool Update() override;
	void Draw() override;

private:
	float ring_x, ring_y, ring_z;
};


//-- 맵 오브젝트

class Snow : public Objects
{
public:
	Snow(float x, float y, float z) :m_x{ x }, m_y{ y }, m_z{ z } {}

	bool Update() override;
	void Draw() override;

private:
	float m_x, m_y, m_z;

};

class Tree : public Objects
{
public:
	Tree(float x, float z) : m_x{ x }, m_z{ z } {};

	bool Update() override;
	void Draw() override;

	float GetColorR() { return m_tree_colorR; }
	float GetColorG() { return m_tree_colorG; }
	float GetColorB() { return m_tree_colorB; }

	void SetColor(float r, float g, float b);

private:
	float m_x, m_z;

	float m_tree_colorR;
	float m_tree_colorG;
	float m_tree_colorB;
};

class Ground : public Objects
{
public:
	Ground();
	~Ground() = default;

	void Draw() override;
	void SetColor(float r, float g, float b);

private:
	float ground_color_r, ground_color_g, ground_color_b;

};

class GameOver_UI : public Objects
{
public:
	GameOver_UI() = default;
	~GameOver_UI() = default;

	void Init();
	void Draw() override;
};

class Score_UI : public Objects
{
public:
	Score_UI() = default;
	~Score_UI() = default;

	void Draw() override;
	
	void SetScore(int score);

	int GetLife() { return life; }
	void SetLife(int _life);
	void DecreaseLife() { life--; }

	void drawInt(int num, float posx, float posy, float scale,
		float colorx = 1, float colory = 1, float colorz = 1);

private:
	int drawNum(int num, int offset, float scale);

	int life = 10;
	int score = 0;
};