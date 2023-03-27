#include "public.h"

#include <map>
#include <string>
#include <mutex>
#include <shared_mutex> // 读写锁，从c++17开始支持

class dns_entry
{
public:
    explicit dns_entry(std::string const name) : m_name(name) {}
    dns_entry() : m_name("None") {}
    std::string GetName() const
    {
        return m_name;
    }

private:
    std::string m_name;
};

class dns_cache
{
    std::map<std::string, dns_entry> entries;
    mutable std::shared_mutex entry_mutex;

public:
    /**
     * @brief 读接口
     *
     * @param domain
     * @return dns_entry
     */
    dns_entry find_entry(std::string const &domain) const
    {
        std::shared_lock<std::shared_mutex> lk(entry_mutex); // 1
        std::map<std::string, dns_entry>::const_iterator const it =
            entries.find(domain);
        const dns_entry &res = (it == entries.end()) ? dns_entry() : it->second;
        printf("Find :%s %s\r\n", domain.c_str(), res.GetName().c_str());
        return res;
    }

    /**
     * @brief 写接口
     *
     * @param domain
     * @param dns_details
     */
    void update_or_add_entry(std::string const &domain,
                             dns_entry const &dns_details)
    {
        std::lock_guard<std::shared_mutex> lk(entry_mutex); // 2
        entries[domain] = dns_details;
        printf("Update :%s %s \r\n", domain.c_str(), dns_details.GetName().c_str());
    }
};

dns_cache dnsCache;

void RwMutexDemo()
{
    dns_entry dnsEntry1("test111");
    dns_entry dnsEntry2("test222");
    dns_entry dnsEntry3("test333");

    dnsCache.update_or_add_entry("test1", dnsEntry1);
    dnsCache.update_or_add_entry("test2", dnsEntry2);
    dnsCache.update_or_add_entry("test3", dnsEntry3);
    dnsCache.find_entry("test1");
    dnsCache.find_entry("test2");
    dnsCache.find_entry("test3");
    dnsCache.find_entry("test4");
    dnsCache.find_entry("test5");
}

// REG_DEMO_FUNC(RwMutexDemo);