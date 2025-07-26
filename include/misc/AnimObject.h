#ifndef ANIMOBJECT_H_
#define ANIMOBJECT_H_
#include <misc/GameObject.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Animator;

class AnimObject : public GameObject
{
public:
	friend class Animator;
	size_t frameIndex{};
	std::string currAnim{};
	bool facingLeft{};
	bool uniDirectional{};
	bool onlyRightTexture{ true };
	float animElapsed{ 0.f };


	bool transitioning{ false };
	float transitionDelay{ 0.1f };
	float transitionElapsed{ 0.f };


	std::unordered_set<std::string> anims{};
	std::unordered_map<std::string, std::unordered_map<std::string, std::vector<sf::Vector2f>>> offsets{};
	std::unordered_map<std::string, std::unordered_map<std::string, std::vector<sf::IntRect>>> texRects{};
	std::unordered_map<std::string, std::vector<sf::Vector2f>> sizes;
	std::unordered_map<std::string, std::vector<Cfg::Textures>> textures;
	std::unordered_map<std::string, std::vector<bool>> repeats;
	std::unordered_map<std::string, std::vector<float>> animDelays;



	void addFrame(const std::string& name_, const sf::Vector2f& offset_, const sf::IntRect& rect_, const sf::Vector2f& size_, const Cfg::Textures& tex_, bool leftFacing_ = false, bool repeating = true, float animDelay_ = 0.f );
	void animate();
protected:
	bool readyToTransition{ false };

public:

	AnimObject();
	virtual ~AnimObject() override = default;
	explicit AnimObject(Cfg::Textures texID_, sf::Vector2f pos_ = { 0.f,0.f }, sf::Vector2f vel_ = { 0.f,0.f }, sf::Vector2f off_ = { 0.f,0.f }, sf::Vector2f size_ = { 0.f,0.f }, sf::IntRect rect_ = { {0,0},{0,0} });
	explicit AnimObject(const std::string& filename);
	AnimObject(const AnimObject&) = default;
	AnimObject& operator=(const AnimObject&) = default;
	AnimObject(AnimObject&&) = default;
	AnimObject& operator=(AnimObject&&) = default;

	void addFrames(const std::string& filename);
	
public:
	void setFacingLeft(bool cond_);
	size_t getNumAnims() { return anims.size(); }
	void setRect(const std::string& anim, const std::string& dir, int idx);
	virtual void render(sf::RenderWindow& tv_) override;
	virtual void update(sf::RenderWindow& tv_, float dt_) override;
	std::string getCurrAnimName();
	void setCurrAnimName(const std::string& animName_);
	bool isFacingLeft();
	bool isTransitioning();
	bool isReadyToTransition();
	bool beginTransitioning();
	virtual void makeTransition() = 0;
	virtual std::string getFSMState() = 0;
	void setFrameIndex(int idx_);
	std::unique_ptr<Animator> animator;
};

#endif