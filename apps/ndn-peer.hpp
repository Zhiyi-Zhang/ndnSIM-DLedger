#ifndef NDN_PEER_H
#define NDN_PEER_H

#include "ns3/ndnSIM/model/ndn-common.hpp"
#include "ns3/ndnSIM/apps/ndn-consumer.hpp"

namespace ns3 {
namespace ndn {

class Peer: public App {
  public:
    // register NS-3 type "Peer"
    static TypeId
    GetTypeId();

    Peer();
    virtual ~Peer(){};

    // (overridden from App) Callback that will be called when Data arrives
    virtual void
    OnData(shared_ptr<const Data> contentObject);

    // (overridden from App) Callback that will be called when Interest arrives
    virtual void
    OnInterest(shared_ptr<const Interest> interest);

  protected:
    // (overridden from App) Processing upon start of the application
    virtual void
    StartApplication();

    // (overridden from App) Processing when application is stopped
    virtual void
    StopApplication();

    // schedule next record generation
    virtual void
    ScheduleNextGeneration();

    // schedule next sync
    virtual void
    ScheduleNextSync();

    void
    SetRandomize(const std::string& value);

    std::string
    GetRandomize() const;

  protected:
    double m_frequency; // Frequency of record generation (in hertz)
    bool m_firstTime;
    Ptr<RandomVariableStream> m_random;
    std::string m_randomType;
    EventId m_sendEvent; ///< @brief EventId of pending "send packet" event

    std::vector<Name> m_tipList; // Tip list
    std::map<Name, Data> m_ledger; // A map name:record storing entire ledger

    int m_weightThreshold;
    int m_entropyThreshold;

  private:
    Name m_routablePrefix; // Node's prefix
    Name m_mcPrefix; // Multicast prefix

    int m_recordNum; // instead of random hash, simply call record1, record2, ...
  
  private:
    // Generates new record and sends notif interest
    void
    GenerateRecord();

    // Fetches record using the given prefix
    void
    FetchRecord(std::string prefix);

};

}
}

#endif
