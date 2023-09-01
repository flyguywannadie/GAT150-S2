#include "CameraComponent.h"
#include "Frame/Actor.h"

namespace max
{
	//CLASS_DEFINITION(CameraComponent);
	bool CameraComponent::Initialize()
	{
		return true;
	}

	bool CameraComponent::InView(max::vec2& point)
	{
		bool inview = false;

		vec2 forward = max::vec2{ 1,0 }.Rotate(m_owner->transform.rotation);
		float rot = forward.Angle();

		float viewanglemax = (rot + max::DegToRad(m_viewAngle));
		float viewanglemin = (rot - max::DegToRad(m_viewAngle));

		if (viewanglemax > Pi) {
			viewanglemax -= TwoPi;
		}
		if (viewanglemin < -Pi) {
			viewanglemin += TwoPi;
		}

		float p1angle = atan2(point.y, point.x);
		if (viewanglemax > viewanglemin) {
			inview = (((viewanglemax > p1angle) && (viewanglemin < p1angle)));
		}
		else {
			inview = (((viewanglemax < p1angle) && (viewanglemin < p1angle)) || ((viewanglemax > p1angle) && (viewanglemin > p1angle)));
		}

		//std::cout << viewanglemax << " to " << viewanglemin << "\r\n" << p1angle << std::endl;

		return inview;
	}

	bool CameraComponent::InView(max::vec2& point1, max::vec2& point2)
	{
		bool inview = false;
		bool inview2 = false;

		bool cansee = false;

		vec2 forward = max::vec2{ 1,0 }.Rotate(m_owner->transform.rotation);
		float rot = forward.Angle();

		float viewanglemax = (rot + max::DegToRad(m_viewAngle));
		float viewanglemin = (rot - max::DegToRad(m_viewAngle));

		if (viewanglemax > Pi) {
			viewanglemax -= TwoPi;
		}
		if (viewanglemin < -Pi) {
			viewanglemin += TwoPi;
		}

		float p1angle = atan2(point1.y, point1.x);
		float p2angle = atan2(point2.y, point2.x);

		bool lineinview = false;

		if (viewanglemax > viewanglemin) {
			inview = (((viewanglemax > p1angle) && (viewanglemin < p1angle)));
			inview2 = (((viewanglemax > p2angle) && (viewanglemin < p2angle)));
			//lineinview = (((viewanglemax < p1angle) && (viewanglemin > p2angle)) || ((viewanglemax < p2angle) && (viewanglemin > p1angle)));
		}
		else {
			inview = (((viewanglemax < p1angle) && (viewanglemin < p1angle)) || ((viewanglemax > p1angle) && (viewanglemin > p1angle)));
			inview2 = (((viewanglemax < p2angle) && (viewanglemin < p2angle)) || ((viewanglemax > p2angle) && (viewanglemin > p2angle)));
		}


		//bool lineinview = DoesLineIntersect(point1, point2, m_owner->transform.position, m_owner->transform.position + (vec2{ 100000,0 }.Rotate(m_owner->transform.rotation)));
		//std::cout << lineinview << std::endl;

		//if either of the two points are in the view it is true, otherwise false
		cansee = (inview || inview2 || lineinview);// || lineinview);
			// check if point 1 is on the outside of min and point 2 is outside of max


		return cansee;
	}

	void CameraComponent::Update(float dt)
	{

	}
}