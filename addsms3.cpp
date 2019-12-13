#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract("addsms3")]] addsms3 : public eosio::contract {
	public:
		static const uint32_t the_party = 1645525342;
		const symbol hodl_symbol;
		addsms3(name receiver, name code, datastream<const char*> ds):contract(receiver, code, ds) {}

		[[eosio::action]]
			void insert(name user, std::string destination, std::string maximum_tokens) {
				require_auth(user);
				smsmarqt_index requests(get_self(), get_first_receiver().value);
				auto iterator = requests.find(user.value);
				requests.emplace(user, [&](auto& row) {
						row.key = user;
						row.id = requests.available_primary_key();
						row.destination = destination;
						row.maximum_tokens = maximum_tokens;
						});
			}
		[[eosio::action]]
			void eraseall() {
					smsmarqt_index requests(get_self(), get_first_receiver().value);
				    auto it = requests.begin();
				    while (it != requests.end()) {
		    		it = requests.erase(it);
    }
			}
	private: 
		struct [[eosio::table]] request {
			uint64_t id;
			std::string destination;
			std::string maximum_tokens;
			name key;
			auto primary_key() const { return id;};
		};
		typedef eosio::multi_index<"requests"_n, request> smsmarqt_index;
};
