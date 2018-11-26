//EOS-Wonderful Token Contract
//https://github.com/humblefirm/eos-wonderful/

//Version 3.0
//Project : Inter-Contract
//Make all eos-wonderful tokens and eos-wonderful contracts interact#include <string>
#include <vector>
#include <eoswonderful.token.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/crypto.h>
#include <eosiolib/time.hpp>
#include <eosiolib/print.h>

using namespace eosio;
using namespace std;
using namespace types;
class token : public contract
{
  public:
	token(account_name self)
		: contract(self)
	{
	}

	//계정 생성 비용 및 설정자 설정
	void setinfo(name manager, asset balance, asset eos)
	{
		//id : 설정 및 계좌 관리자
		//token : 계정 생성비 (토큰)
		//coin : 계정 생성비 (코인)

		Check_asset(balance, "COF");
		Check_asset(eos, "EOS");

		info_table info(_self, _self);
		auto itr_info = info.find(0);
		if (itr_info == info.end())
		{
			require_auth(_self);
			info.emplace(_self, [&](auto &r) {
				r.id = 0;
				r.manager = manager;
				r.balance = balance;
				r.eos = eos;
			});
		}
		else
		{
			require_auth(itr_info->manager);
			info.modify(itr_info, _self, [&](auto &r) {
				r.manager = manager;
				r.balance = balance;
				r.eos = eos;
			});
		}
	}

	//토큰 발행 - key
	void mintk(public_key to, asset amount, string memo)
	{
		//대상자|발행량|메모

		//권한 확인
		info_table info(_self, _self);
		auto itr_info = info.find(0);
		require_auth(itr_info->manager);

		//정확성 확인
		Check_asset(amount, "COF");
		Check_memo(memo);

		//발행
		balance_add_key(to, amount, itr_info->manager, false);
	}

	//토큰 발행 - name
	void mintn(name to, asset amount, string memo)
	{
		//대상자|발행량|메모

		//권한 확인
		info_table info(_self, _self);
		auto itr_info = info.find(0);
		require_auth(itr_info->manager);

		//정확성 확인
		Check_asset(amount, "COF");
		Check_memo(memo);

		//발행
		balance_add_name(to, amount, itr_info->manager);
	}

	void transferkk(public_key from, public_key to, asset amount, string memo,
					asset fee, signature sig, name sa)
	{
		//송신자|수신자|액수|메모|{sadata}
		require_auth(sa);

		keybalance_table keybalance(_self, _self);
		auto itr_from = keybalance.find(keytoid(from));
		verify_sig_transfer(from, to, amount, memo, fee, itr_from->nonce, sig);
		bool iseos = is_eos(amount);
		Check_memo(memo);

		balance_sub_key(from, amount, sa, true);
		balance_add_key(to, amount, sa, false);
	}
	void transferkn(public_key from, name to, asset amount, string memo,
					asset fee, signature sig, name sa)
	{
		//송신자|수신자|액수|메모|{sadata}
		require_auth(sa);

		keybalance_table keybalance(_self, _self);
		auto itr_from = keybalance.find(keytoid(from));
		verify_sig_transfer(from, to, amount, memo, fee, itr_from->nonce, sig);
		bool iseos = is_eos(amount);
		Check_memo(memo);

		balance_sub_key(from, amount, sa, true);
		balance_add_name(to, amount, sa);
	}
	void transfernn(name from, name to, asset amount, string memo)
	{
		//송신자|수신자|액수|메모
		require_auth(from);
		bool iseos = is_eos(amount);
		Check_memo(memo);

		balance_sub_name(from, amount, from);
		balance_add_name(to, amount, from);
	}
	void transfernk(name from, public_key to, asset amount, string memo)
	{
		//송신자|수신자|액수|메모
		require_auth(from);
		bool iseos = is_eos(amount);
		Check_memo(memo);

		balance_sub_name(from, amount, from);
		balance_add_key(to, amount, from);
	}

	void income()
	{
	}

  private:
	int fast_atoi(const char *str)
	{
		int val = 0;
		while (*str)
		{
			val = val * 10 + (*str++ - '0');
		}
		return val;
	}
	bool is_key(string account)
	{
		printi(account.size());
		if (account.size() == 53)
			return true;
		return false;
	}
	bool is_eos(asset amount)
	{
		if (amount.symbol == string_to_symbol(4, "EOS"))
		{
			Check_asset(amount, "EOS");
			return true;
		}
		else
			Check_asset(amount, "COF");
		return false;
	}
	void Check_asset(asset amount, string symbol)
	{
		eosio_assert(amount.symbol == string_to_symbol(4, symbol.c_str()),
					 "This symbol not support");
		eosio_assert(amount.is_valid(), "invalid quantity");
		eosio_assert(amount.amount >= 0, "must transfer positive quantity");
	}
	void Check_memo(string memo)
	{
		eosio_assert(memo.size() <= 256, "memo has more than 256 bytes");
	}
	uint64_t keytoid(public_key key)
	{
		uint64_t ret = 0;
		int i = 0;
		for (; i < 6; i++)
		{
			int a = key.data[i + 1];
			a = a < 0 ? 256 + a : a;
			ret += a << (i * 4);
		}
		return ret;
	}

	void balance_add_key(public_key account, asset amount, name ram_payer, bool upnonce = false)
	{
		keybalance_table keybalance(_self, _self);
		auto itr_balance = keybalance.find(keytoid(account));
		if (itr_balance == keybalance.end())
		{
			keybalance.emplace(ram_payer, [&](auto &r) {
				r.id = keytoid(account);
				r.user = account;
				r.nonce = 0;
				r.balance.amount = 0;
				r.balance.symbol = string_to_symbol(4, "COF");
				r.eos.amount = 0;
				r.eos.symbol = string_to_symbol(4, "EOS");
				if (amount.symbol == string_to_symbol(4, "EOS"))
					r.eos += amount;
				else
					r.balance += amount;
			});
		}
		else
		{
			keybalance.modify(itr_balance, ram_payer, [&](auto &r) {
				if (amount.symbol == string_to_symbol(4, "EOS"))
					r.eos += amount;
				else
					r.balance += amount;
				if (upnonce)
					r.nonce++;
			});
		}
	}
	void balance_add_name(name account, asset amount, name ram_payer)
	{
		namebalance_table namebalance(_self, _self);
		auto itr_balance = namebalance.find(account);
		if (itr_balance == namebalance.end())
		{
			namebalance.emplace(ram_payer, [&](auto &r) {
				r.id = account;
				r.balance.amount = 0;
				r.balance.symbol = string_to_symbol(4, "COF");
				r.eos.amount = 0;
				r.eos.symbol = string_to_symbol(4, "EOS");
				if (amount.symbol == string_to_symbol(4, "EOS"))
					r.eos += amount;
				else
					r.balance += amount;
			});
		}
		else
		{
			namebalance.modify(itr_balance, ram_payer, [&](auto &r) {
				if (amount.symbol == string_to_symbol(4, "EOS"))
					r.eos += amount;
				else
					r.balance += amount;
			});
		}
	}
	void balance_sub_key(public_key account, asset amount, name ram_payer, bool upnonce = false)
	{
		keybalance_table keybalance(_self, _self);
		auto itr_balance = keybalance.find(keytoid(account));
		eosio_assert(itr_balance != keybalance.end(), "Account doesn't exists");
		keybalance.modify(itr_balance, ram_payer, [&](auto &r) {
			if (amount.symbol == string_to_symbol(4, "EOS"))
				r.eos -= amount;
			else
				r.balance -= amount;
			eosio_assert(r.eos.amount >= 0 && r.balance.amount >= 0, "Overdrawn balance");
			if (upnonce)
				r.nonce++;
		});
	}
	void balance_sub_name(name account, asset amount, name ram_payer)
	{
		namebalance_table namebalance(_self, _self);
		auto itr_balance = namebalance.find(account);
		eosio_assert(itr_balance != namebalance.end(), "Account doesn't exists");
		namebalance.modify(itr_balance, ram_payer, [&](auto &r) {
			if (amount.symbol == string_to_symbol(4, "EOS"))
				r.eos -= amount;
			else
				r.balance -= amount;
			eosio_assert(r.eos.amount >= 0 && r.balance.amount >= 0, "Overdrawn balance");
		});
	}
	void verify_sig_transfer(public_key from, name to, asset amount, string memo,
							 asset fee, int64_t nonce, signature sig)
	{

		char strchar[256];
		strncpy(strchar, memo.c_str(), sizeof(strchar));
		strchar[sizeof(strchar) - 1] = 0;

		checksum256 digest;
		char potato[34 + 8 * 2 + 256 + 8 * 2];

		memcpy(potato, &from, sizeof(from));
		memcpy(potato + 34, &to, sizeof(to));
		memcpy(potato + 34 + 8, &amount.amount, sizeof(amount.amount));
		memcpy(potato + 34 + 8 + 8, &strchar, sizeof(strchar));
		memcpy(potato + 34 + 8 + 8 + 256, &fee.amount, sizeof(fee.amount));
		memcpy(potato + 34 + 8 + 8 + 256 + 8, &nonce, sizeof(nonce));

		sha256(potato, sizeof(potato), &digest);

		assert_recover_key(&digest, (const char *)&sig, sizeof(sig), (const char *)&from, sizeof(from));
	}
	void verify_sig_transfer(public_key from, public_key to, asset amount, string memo,
							 asset fee, int64_t nonce, signature sig)
	{

		char strchar[256];
		strncpy(strchar, memo.c_str(), sizeof(strchar));
		strchar[sizeof(strchar) - 1] = 0;

		checksum256 digest;
		char potato[34 * 2 + 8 + 256 + 8 * 2];

		memcpy(potato, &from, sizeof(from));
		memcpy(potato + 34, &to, sizeof(to));
		memcpy(potato + 34 + 34, &amount.amount, sizeof(amount.amount));
		memcpy(potato + 34 + 34 + 8, &strchar, sizeof(strchar));
		memcpy(potato + 34 + 34 + 8 + 256, &fee.amount, sizeof(fee.amount));
		memcpy(potato + 34 + 34 + 8 + 256 + 8, &nonce, sizeof(nonce));

		sha256(potato, sizeof(potato), &digest);

		assert_recover_key(&digest, (const char *)&sig, sizeof(sig), (const char *)&from, sizeof(from));
	}
};

#undef EOSIO_ABI
#define EOSIO_ABI(TYPE, MEMBERS)                                                                                                 \
	extern "C"                                                                                                                   \
	{                                                                                                                            \
		void apply(uint64_t receiver, uint64_t code, uint64_t action)                                                            \
		{                                                                                                                        \
			auto self = receiver;                                                                                                \
			TYPE thiscontract(self);                                                                                             \
			if (action == N(onerror))                                                                                            \
			{                                                                                                                    \
				/* onerror is only valid if it is for the "eosio" code account and authorized by "eosio"'s "active permission */ \
				eosio_assert(code == N(eosio), "onerror action's are only valid from the \"eosio\" system account");             \
			}                                                                                                                    \
			if (code == self)                                                                                                    \
			{                                                                                                                    \
				if (action != N(income))                                                                                         \
				{                                                                                                                \
					switch (action)                                                                                              \
					{                                                                                                            \
						EOSIO_API(TYPE, MEMBERS)                                                                                 \
					}                                                                                                            \
					/* does not allow destructor of thiscontract to run: eosio_exit(0);    */                                    \
				}                                                                                                                \
			}                                                                                                                    \
			else if (code == N(eosio.token) && action == N(transfer))                                                            \
			{                                                                                                                    \
				execute_action(&thiscontract, &token::income);                                                                   \
			}                                                                                                                    \
		}                                                                                                                        \
	}

EOSIO_ABI(token, (setinfo)(mintk)(mintn)(transferkk)(transferkn)(transfernn)(transfernk)(income))

// 가시밭길이더라도 자주적 사고를 하는 이의 길을 가십시오. 비판과 논란에 맞서서 당신의 생각을 당당히 밝히십시오. 당신의 마음이 시키는 대로 하십시오. '별난 사람'이라고 낙인찍히는 것보다 순종이라는 오명에 무릎 꿇는 것을 더 두려워하십시오. 당신이 중요하다고 생각하는 이념을 위해서라면 온 힘을 다해 싸우십시오.
// Thomas J. Watson