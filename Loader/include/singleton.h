#ifndef __SINGLETON_H__
#define __SINGLETON_H__

namespace wwist {

	/** Base Class
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
		Singleton(const Singleton&) = delete;
		void operator=(const Singleton&) = delete;

	protected:
		Singleton() {};
		~Singleton() {};

	};

}

#endif // __SINGLETON_H__