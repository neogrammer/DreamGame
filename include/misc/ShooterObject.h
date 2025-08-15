#ifndef SHOOTEROBJECT_H__
#define SHOOTEROBJECT_H__
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <map>
#include <set>

class AnimObject;
/// <summary>
/// Meant to be for lateral inheritance that couples with AnimObject Only
/// </summary>
class ShooterObject
{
	void loadFile(const std::string& weaponFile_);


	AnimObject& augmented;
protected:
	/// <summary>
	/// tied to the animated object augmented with this class
	/// </summary>
	std::map<std::string, std::map<std::string, std::vector<sf::Vector2f>>> frameAnchors{};
	//std::set<std::string> weaponSet{};
	// by type, each vector of bullet types this entity uses is tracked
	//std::map<std::string, std::vector<Projectile*>> liveProjectiles{};


public:
	ShooterObject(AnimObject& augmented_, const std::string& anchorFile_);
	~ShooterObject() = default;
	ShooterObject(const ShooterObject&) = default;
	ShooterObject& operator=(const ShooterObject&) = default;
	ShooterObject(ShooterObject&&) = delete;
	ShooterObject& operator=(ShooterObject&&) = delete;
};

#endif