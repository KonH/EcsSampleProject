#pragma once

namespace Sample::Systems {
	class System {
	public:
		virtual ~System() = default;

		virtual void Init() {}

		virtual void Update() {}
	};
}