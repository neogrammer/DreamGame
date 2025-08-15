
#include <iostream>
#include <fstream>
#include <actors/Player.h>
#include <misc/Animator.h>

void AnimObject::addFrame(const std::string& name_, const sf::Vector2f& offset_, const sf::IntRect& rect_, const sf::Vector2f& size_, const Cfg::Textures& tex_, bool leftFacing, bool repeating, float animDelay_)
{
		auto found = anims.find(name_);
		bool alreadyCreated = false;
		if (found != anims.end())
		{
			if (!uniDirectional)
			{
				if (leftFacing)
				{
					auto tmp0 = offsets.find(name_);
					if (tmp0 == offsets.end())
						offsets.emplace(std::pair<std::string, std::unordered_map<std::string, std::vector<sf::Vector2f>>>{std::string(name_), std::unordered_map<std::string, std::vector<sf::Vector2f>>{}});

					auto tmp1 = offsets.find(name_);
					if (tmp1 == offsets.end())
						texRects.emplace(std::pair<std::string, std::unordered_map<std::string, std::vector<sf::IntRect>>>{std::string(name_), std::unordered_map<std::string, std::vector<sf::IntRect>>{}});

					auto tmp = offsets[name_].find("Left");
					if (tmp == offsets[name_].end())
					{
						// need to make a new item with the tag Uni
						offsets[name_].emplace(std::pair<std::string, std::vector<sf::Vector2f>>{"Left", std::vector<sf::Vector2f>{}});
						offsets[name_]["Left"].emplace_back(offset_);
						// safe to assume others need to be made as well
						texRects[name_].emplace(std::pair<std::string, std::vector<sf::IntRect>>{"Left", std::vector<sf::IntRect>{}});
						texRects[name_]["Left"].emplace_back(rect_);

						if (offsets[name_]["Left"].size() - 1 == sizes[name_].size())
							sizes[name_].emplace_back(size_);
						if (offsets[name_]["Left"].size() - 1 == textures[name_].size())
							textures[name_].emplace_back(tex_);
						if (offsets[name_]["Left"].size() - 1 == repeats[name_].size())
							repeats[name_].emplace_back(repeating);
						if (offsets[name_]["Left"].size() - 1 == animDelays[name_].size())
							animDelays[name_].emplace_back(animDelay_);
					}
					else
					{
						offsets[name_]["Left"].emplace_back(offset_);
						texRects[name_]["Left"].emplace_back(rect_);

						if (offsets[name_]["Left"].size() - 1 == sizes[name_].size())
							sizes[name_].emplace_back(size_);
						if (offsets[name_]["Left"].size() - 1 == textures[name_].size())
							textures[name_].emplace_back(tex_);
						if (offsets[name_]["Left"].size() - 1 == repeats[name_].size())
							repeats[name_].emplace_back(repeating);
						if (offsets[name_]["Left"].size() - 1 == animDelays[name_].size())
							animDelays[name_].emplace_back(animDelay_);
					}
				}
				else
				{
					auto tmp0 = offsets.find(name_);
					if (tmp0 == offsets.end())
						offsets.emplace(std::pair<std::string, std::unordered_map<std::string, std::vector<sf::Vector2f>>>{std::string(name_), std::unordered_map<std::string, std::vector<sf::Vector2f>>{}});

					auto tmp1 = offsets.find(name_);
					if (tmp1 == offsets.end())
						texRects.emplace(std::pair<std::string, std::unordered_map<std::string, std::vector<sf::IntRect>>>{std::string(name_), std::unordered_map<std::string, std::vector<sf::IntRect>>{}});


					auto tmp = offsets[name_].find("Right");
					if (tmp == offsets[name_].end())
					{
						// need to make a new item with the tag Uni
						offsets[name_].emplace(std::pair<std::string, std::vector<sf::Vector2f>>{"Right", std::vector<sf::Vector2f>{}});
						offsets[name_]["Right"].emplace_back(offset_);
						// safe to assume others need to be made as well
						texRects[name_].emplace(std::pair<std::string, std::vector<sf::IntRect>>{"Right", std::vector<sf::IntRect>{}});
						texRects[name_]["Right"].emplace_back(rect_);

						if (offsets[name_]["Right"].size() - 1 == sizes[name_].size())
							sizes[name_].emplace_back(size_);
						if (offsets[name_]["Right"].size() - 1 == textures[name_].size())
							textures[name_].emplace_back(tex_);
						if (offsets[name_]["Right"].size() - 1 == repeats[name_].size())
							repeats[name_].emplace_back(repeating);
						if (offsets[name_]["Right"].size() - 1 == animDelays[name_].size())
							animDelays[name_].emplace_back(animDelay_);
					}
					else
					{
						offsets[name_]["Right"].emplace_back(offset_);
						texRects[name_]["Right"].emplace_back(rect_);

						if (offsets[name_]["Right"].size() - 1 == sizes[name_].size())
							sizes[name_].emplace_back(size_);
						if (offsets[name_]["Right"].size() - 1 == textures[name_].size())
							textures[name_].emplace_back(tex_);
						if (offsets[name_]["Right"].size() - 1 == repeats[name_].size())
							repeats[name_].emplace_back(repeating);
						if (offsets[name_]["Right"].size() - 1 == animDelays[name_].size())
							animDelays[name_].emplace_back(animDelay_);
					}
				}
				
				
			}
			else
			{
				auto tmp0 = offsets.find(name_);
				if (tmp0 == offsets.end())
					offsets.emplace(std::pair<std::string, std::unordered_map<std::string, std::vector<sf::Vector2f>>>{std::string(name_), std::unordered_map<std::string, std::vector<sf::Vector2f>>{}});

				auto tmp1 = offsets.find(name_);
				if (tmp1 == offsets.end())
					texRects.emplace(std::pair<std::string, std::unordered_map<std::string, std::vector<sf::IntRect>>>{std::string(name_), std::unordered_map<std::string, std::vector<sf::IntRect>>{}});


				auto tmp = offsets[name_].find("Uni");
				if (tmp == offsets[name_].end())
				{
					// need to make a new item with the tag Uni
					offsets[name_].emplace(std::pair<std::string, std::vector<sf::Vector2f>>{"Uni", std::vector<sf::Vector2f>{}});
					offsets[name_]["Uni"].emplace_back(offset_);
					// safe to assume others need to be made as well
					texRects[name_].emplace(std::pair<std::string, std::vector<sf::IntRect>>{"Uni", std::vector<sf::IntRect>{}});
					texRects[name_]["Uni"].emplace_back(rect_);	
					sizes[name_].emplace_back(size_);
					textures[name_].emplace_back(tex_);
					repeats[name_].emplace_back(repeating);
					animDelays[name_].emplace_back(animDelay_);
				}
				else
				{
					offsets[name_]["Uni"].emplace_back(offset_);
					texRects[name_]["Uni"].emplace_back(rect_);
					sizes[name_].emplace_back(size_);
					textures[name_].emplace_back(tex_);
					repeats[name_].emplace_back(repeating);
					animDelays[name_].emplace_back(animDelay_);
				}
			}
		}
		else if (found == anims.end())
		{

			if (sizes.empty())
			{
				sizes[name_] = std::vector<sf::Vector2f>{};
				sizes[name_].clear();
			}

			if (textures.empty())
			{
				textures[name_] = std::vector<Cfg::Textures>{};
				textures[name_].clear();
			}

			if (repeats.empty())
			{
				repeats[name_] = std::vector<bool>{};
				repeats[name_].clear();
			}
			if (animDelays.empty())
			{
				animDelays[name_] = std::vector<float>{};
				animDelays[name_].clear();
			}

			// name not in set, lets add it
			anims.insert(name_);


			// guaranteed to have name in anims set now
			if (!uniDirectional)
			{
				if (leftFacing)
				{
					auto tmp = offsets.find(name_);
					if (tmp == offsets.end())
					{
						offsets.emplace(std::pair<std::string, std::unordered_map<std::string, std::vector<sf::Vector2f>>>{std::string(name_), std::unordered_map<std::string, std::vector<sf::Vector2f>>{}});
						auto tmpInner = offsets[name_].find("Left");
						if (tmpInner == offsets[name_].end())	
							offsets[name_].emplace(std::pair<std::string, std::vector<sf::Vector2f>>{ "Left", std::vector<sf::Vector2f>{} });
					}
					offsets[name_]["Left"].emplace_back(offset_);


					auto tmp2 = texRects.find(name_);
					if (tmp2 == texRects.end())
					{
						texRects.emplace(std::pair<std::string, std::unordered_map<std::string, std::vector<sf::IntRect>>>{std::string(name_), std::unordered_map<std::string, std::vector<sf::IntRect>>{}});
						auto tmpInner = texRects[name_].find("Left");
						if (tmpInner == texRects[name_].end())
							texRects[name_].emplace(std::pair<std::string, std::vector<sf::IntRect>>{ "Left", std::vector<sf::IntRect>{} });
					}
					texRects[name_]["Left"].emplace_back(rect_);


				}
				else
				{
					auto tmp = offsets.find(name_);
					if (tmp == offsets.end())
					{
						offsets.emplace(std::pair<std::string, std::unordered_map<std::string, std::vector<sf::Vector2f>>>{std::string(name_), std::unordered_map<std::string, std::vector<sf::Vector2f>>{}});
						auto tmpInner = offsets[name_].find("Right");
						if (tmpInner == offsets[name_].end())
							offsets[name_].emplace(std::pair<std::string, std::vector<sf::Vector2f>>{ "Right", std::vector<sf::Vector2f>{} });
					}
					offsets[name_]["Right"].emplace_back(offset_);

					auto tmp2 = texRects.find(name_);
					if (tmp2 == texRects.end())
					{
						texRects.emplace(std::pair<std::string, std::unordered_map<std::string, std::vector<sf::IntRect>>>{std::string(name_), std::unordered_map<std::string, std::vector<sf::IntRect>>{}});
						auto tmpInner = texRects[name_].find("Right");
						if (tmpInner == texRects[name_].end())
							texRects[name_].emplace(std::pair<std::string, std::vector<sf::IntRect>>{ "Right", std::vector<sf::IntRect>{} });
					}
					texRects[name_]["Right"].emplace_back(rect_);

				}
			}
			else
			{
				auto tmp = offsets.find(name_);
				if (tmp == offsets.end())
				{
					offsets.emplace(std::pair<std::string, std::unordered_map<std::string, std::vector<sf::Vector2f>>>{std::string(name_), std::unordered_map<std::string, std::vector<sf::Vector2f>>{}});
					auto tmpInner = offsets[name_].find("Uni");
					if (tmpInner == offsets[name_].end())
						offsets[name_].emplace(std::pair<std::string, std::vector<sf::Vector2f>>{ "Uni", std::vector<sf::Vector2f>{} });
				}
				offsets[name_]["Uni"].emplace_back(offset_);

				auto tmp2 = texRects.find(name_);
				if (tmp2 == texRects.end())
				{
					texRects.emplace(std::pair<std::string, std::unordered_map<std::string, std::vector<sf::IntRect>>>{std::string(name_), std::unordered_map<std::string, std::vector<sf::IntRect>>{}});
					auto tmpInner = texRects[name_].find("Uni");
					if (tmpInner == texRects[name_].end())
						texRects[name_].emplace(std::pair<std::string, std::vector<sf::IntRect>>{ "Uni", std::vector<sf::IntRect>{} });
				}
				texRects[name_]["Uni"].emplace_back(rect_);

			}

			sizes[name_].emplace_back(size_);
			textures[name_].emplace_back(tex_);
			repeats[name_].emplace_back(repeating);
			animDelays[name_].emplace_back(animDelay_);

		}

		// frame should be loaded properly
		if (sizes.size() != textures.size() || sizes.size() != repeats.size() || sizes.size() != animDelays.size())
		{
			std::cout << "\nAnimFrame adding went awry\n" << std::endl;
		}
}


void AnimObject::animate()
{
	frameIndex++;
	const std::string& dir = uniDirectional ? "Uni" : (isFacingLeft() ? ((onlyRightTexture) ? "Right" : "Left") : "Right");

	if (frameIndex >= texRects[currAnim][dir].size())
	{
		if (repeats[currAnim][0])
			frameIndex = 0;
		else
			frameIndex = texRects[currAnim][dir].size() - 1;
	}
	setRect(currAnim, dir, (int)frameIndex);
}

void AnimObject::addFrames(const std::string& filename)
{
	std::fstream iFile{ filename };

	if (iFile.is_open())
	{
		int numAnims;
		iFile >> numAnims;

		int onlyright;
		iFile >> onlyright;

		if (onlyright == 0)
		{
			onlyRightTexture = false;
		}
		else if (onlyright == 1)
		{
			onlyRightTexture = true;
		}
		else
		{
			std::cout << "Animation file not being read correctly" << std::endl;
		}
		
		for (int a = 0; a < numAnims; a++)
		{
			std::string animName;
			int dir; // 0 - left 1 - right 2 - uni
			int numFrames;

			iFile >> animName;

			bool repeating{};
			int repeating_;
			iFile >> repeating_;
			if (repeating_ == 1)
				repeating = true;
			else
				repeating = false;

			int dly;
			iFile >> dly;
			float delay = (float)dly / 1000.f;


			iFile >> dir;
			iFile >> numFrames;

			std::vector<sf::Vector2f> offs{};

			std::vector<sf::IntRect> recs{};
			Cfg::Textures texs{Cfg::Textures::UNKNOWN};
		
			offs.reserve(numFrames);
			recs.reserve(numFrames);
			
			sf::Vector2f animSize{};
			sf::Vector2f recSize{};

			std::string texName; 

			iFile >> animSize.x >> animSize.y;
			iFile >> recSize.x >> recSize.y;
			iFile >> texName;

			
			
			if (texName == "PlayerSheet132x170")
			{ 
				texs = Cfg::Textures::PlayerSheet132x170;
			}
			else if (texName == "MegamanSheet130x160")
			{
				texs = Cfg::Textures::MegamanSheet130x160;
			}
			else if (texName == "SmileyJoe126x120")
			{
				texs = Cfg::Textures::SmileyJoe126x126;
			}
			else if (texName == "BusterBullet28x18")
			{
				texs = Cfg::Textures::BusterBullet28x18;
			}
			else
			{
				std::cerr << "Unknown TexName in file: " << filename << std::endl;
			}

			for (int i = 0; i < numFrames; i++)
			{
				sf::Vector2f tmp{};
				iFile >> tmp.x >> tmp.y;
				offs.emplace_back(tmp);
			}
			int numCols;
			int startCol;
			int numRows;
			int startRow;
		
			int totalCols;
			iFile >> totalCols >> numCols >> numRows >> startCol >> startRow;
			bool firstRow = true;
			for (int y = 0; y < numRows; y++)
			{
				for (int x = 0; x < numCols; x++)
				{
					int i = y * numCols + x;
					
					sf::IntRect tmp{};
					if (firstRow)
					{	
						tmp.position.x = (int)(startCol * recSize.x) + (int)(x * recSize.x);
						tmp.position.y = (int)(startRow * recSize.y) + (int)(y * recSize.y);
					}
					else
					{		
						tmp.position.x = (int)(x * recSize.x);
						tmp.position.y = (int)(startRow * recSize.y) + (int)(y * recSize.y);
					}


					tmp.size.x = (int)recSize.x;
					tmp.size.y = (int)recSize.y;
					
					if (onlyRightTexture && dir == 0)
					{
						sf::IntRect reverseRect{ {0,0},{0,0} };

						if (firstRow)
						{
							reverseRect.position.x = (int)(startCol * recSize.x) + (int)(x * recSize.x) + (int)recSize.x;
							reverseRect.position.y = (int)(startRow * recSize.y) + (int)(y * recSize.y);
		
						}
						else
						{
							reverseRect.position.x = (int)(x * recSize.x) + (int)recSize.x;
							reverseRect.position.y = (int)(startRow * recSize.y) + (int)(y * recSize.y);
						}

						reverseRect.size.x = (-1 * tmp.size.x);
						reverseRect.size.y = (int)recSize.y;

						recs.emplace_back(reverseRect);
					}
					else
					{
						recs.emplace_back(tmp);
					}
				}
			}

			
			
			if (dir == 2)
				uniDirectional = true;

			for (int j = 0; j < numFrames; j++)
			{
				addFrame(animName, offs.at(j), recs.at(j), animSize, texs, (dir == 0) ? true : false, repeating, delay);
			}

		}

		iFile.close();
	}
	else
	{
		std::cout << "\nFile not opened " << filename << std::endl;
	}
}

void AnimObject::setFacingLeft(bool cond_)
{
	facingLeft = cond_;
}

void AnimObject::setRect(const std::string& anim, const std::string& dir, int idx)
{

	if (idx >= texRects[anim][dir].size())
	{
		return;
	}

	GameObject::setRect(texRects[anim][dir][idx]);
	//setFrameIndex(idx);
}

AnimObject::AnimObject()
	: GameObject{}
	, animator{std::make_unique<Animator>(this)}
{
}

AnimObject::AnimObject(Cfg::Textures texID_, sf::Vector2f pos_, sf::Vector2f vel_, sf::Vector2f off_, sf::Vector2f size_, sf::IntRect rect_)
	: GameObject{ texID_, pos_, vel_, off_, size_, rect_ }
	, animator{ std::make_unique<Animator>(this) }
{
}

AnimObject::AnimObject(const std::string& filename)
	: GameObject{}
	, animator{ std::make_unique<Animator>(this) }
{
}

void AnimObject::render(sf::RenderWindow& tv_)
{
	if (currAnim != getFSMState() && getFSMState() != "None")
	{
		const std::string& dir = uniDirectional ? "Uni" : (isFacingLeft() ? ((onlyRightTexture) ? "Right" : "Left") : "Right");

		auto tmp = currAnim;

		currAnim = getFSMState();

		auto tmp2 = currAnim;
		bool staySameIndex = false;
		if (dynamic_cast<Player*>(this) != nullptr)
		{
			

			if (tmp != tmp2)
			{
				if (tmp == "Moving" || tmp == "MovingAndShooting")
				{
					if (tmp2 == "Moving" || tmp2 == "MovingAndShooting")
					{
						staySameIndex = true;
					}
				}
				else if (tmp == "Jumping" || tmp == "JumpingAndShooting")
				{
					if (tmp2 == "Jumping" || tmp2 == "JumpingAndShooting")
					{
						staySameIndex = true;
					}
				}
				else if (tmp == "Falling" || tmp == "FallingAndShooting")
				{
					if (tmp2 == "Falling" || tmp2 == "FallingAndShooting")
					{
						staySameIndex = true;
					}
				}
				else if (tmp == "Landing" || tmp == "LandingAndShooting")
				{
					if (tmp2 == "Landing" || tmp2 == "LandingAndShooting")
					{
						staySameIndex = true;
					}
				}
			}
		}


		if (staySameIndex == false)
			frameIndex = 0;
		else
		{
			if (animElapsed >= animDelays[currAnim][0])
			{
				if (frameIndex >= texRects[currAnim][dir].size() - 1)
				{
					if (repeats[currAnim][0])
						frameIndex = 0;
					else
						frameIndex = texRects[currAnim][dir].size() - 1;
				}
				else
				{
					frameIndex += 1;
				}
			}
		}
		
		setRect(currAnim, dir, (int)frameIndex);
	}

	if (facingLeft && !uniDirectional && onlyRightTexture)
	{
		auto old = getRect();
		sf::IntRect tmp = getRect();
		tmp.position.x += tmp.size.x;
		tmp.size.x = -tmp.size.x;
		GameObject::setRect(tmp);
		GameObject::render(tv_);
		GameObject::setRect(old);
	}
	else
	{
		GameObject::render(tv_);
	}

}

void AnimObject::update(sf::RenderWindow& tv_, float dt_)
{

	// if not trying to transition out and not the last frame yet, keep animating
	if (transitioning && frameIndex >= texRects[currAnim][((uniDirectional) ? "Uni" : ((isFacingLeft()) ? ((onlyRightTexture) ? "Right" : "Left") : "Right"))].size() - 1)
	{
		// we are now transitioning and on the last frame
		transitionElapsed += dt_;
		if (transitionElapsed >= transitionDelay)
		{
			transitionElapsed = 0.f;
			transitioning = false;
			readyToTransition = true;
		}
	}
	else
	{
		animElapsed += dt_;
		if (frameIndex >= animDelays[currAnim].size())
		{
			frameIndex = ((animDelays[currAnim].size() > 0) ? animDelays[currAnim].size() - 1 : 0);
		}

		if (animElapsed >= animDelays[currAnim][frameIndex])
		{
			animElapsed = 0.f;
			animate();
		}
	}
	
	if (readyToTransition) makeTransition();

	GameObject::update(tv_, dt_);
}

std::string AnimObject::getCurrAnimName()
{
	return currAnim;
}

void AnimObject::setCurrAnimName(const std::string& animName_)
{
	currAnim = animName_;
}

bool AnimObject::isFacingLeft()
{
	return facingLeft;
}

bool AnimObject::isTransitioning()
{
	return transitioning;
}

bool AnimObject::isReadyToTransition()
{
	return readyToTransition;
}

bool AnimObject::beginTransitioning()
{
	return transitioning = true;
}

void AnimObject::setFrameIndex(int idx_)
{
	if (idx_ < texRects[currAnim][((uniDirectional) ? "Uni" : ((isFacingLeft()) ? ((onlyRightTexture) ? "Right" : "Left") : "Right"))].size() && idx_ >= 0)
		frameIndex = idx_;
}
