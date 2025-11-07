#ifndef SINGLETON_INCLUDE
#define SINGLETON_INCLUDE

namespace wwist {

	/**
	 * @brief Singleton base class.
	 * @attention Define “friend” in the inheritance target.
	 * @code
	 *		class ___ : public wwist::Singleton< ___ >
	 *		{
	 *		private:
	 *			friend wwist::Singleton< ___ >;
	 *
	 *		...
	 *		}
	 * @endcode
	 */
	template <typename T>
	class Singleton {
	public:
		static T& GetInstance() {
			static T instance;
			return instance;
		}

	private:
		Singleton(const Singleton&)		 = delete;
		void operator=(const Singleton&) = delete;

	protected:
		Singleton()	 = default;
		~Singleton() = default;

	};

}

#endif // SINGLETON_INCLUDE