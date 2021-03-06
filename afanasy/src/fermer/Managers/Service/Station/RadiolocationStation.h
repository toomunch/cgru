#ifndef __FERMERMESSAGE__
#define __FERMERMESSAGE__

#include "libafanasy/name_af.h"

#include <QtNetwork/QTcpSocket>
#include <boost/shared_ptr.hpp>

#include "libafanasy/environment.h"
#include "libafqt/qenvironment.h"
#include "libafanasy/msg.h"
#include "watch/monitorhost.h"

#include "libafqt/qthreadclientsend.h"
#include "libafqt/qthreadclientup.h"


#include "common.h"
#include "state.hpp"

namespace afermer
{

class Waves
{
public:
    AFERMER_TYPEDEF_SMART_PTRS(af::Msg)
    AFERMER_DEFINE_CREATE_FUNC_2_ARGS(af::Msg, size_t, size_t)
    AFERMER_DEFINE_CREATE_FUNC_2_ARGS(af::Msg, size_t, af::Af *)
};

class RadiolocationStation : public QObject
{
    Q_OBJECT

protected:
    QTcpSocket socket;
    af::Address addresses;


private slots:
    void pullMessage( af::Msg *msg);
    void connectionLost();

signals:
    void outputComplited();

public:
    AFERMER_TYPEDEF_SMART_PTRS(RadiolocationStation)
    AFERMER_DEFINE_CREATE_FUNC(RadiolocationStation)

    static bool QStringFromMsg(QString&, Waves::Ptr);
    static int getAvalibleSlotsAndJobNames(af::Render *, int, QString&, QList<int>&);
    static void getItemInfo( std::ostringstream&, const std::string &, const std::string &, int);


    bool setParameter(const std::string&, const std::vector<int>&, const std::string&, const std::string&, bool);
    bool setOperation(const std::string&, const std::vector<int>&, const std::string&);

    af::Environment* ENV;

    RadiolocationStation();
    ~RadiolocationStation();
    Waves::Ptr push(const std::ostringstream&);
    void addJobId( int i_jid, bool i_add);

    size_t getId();
    size_t getUserId();
    void getServerIPAddress(std::string&);
    void getUserName(std::string&);

    MonitorHost* m_monitor;
    size_t monitor_id;

    void getTaskOutput(QString&, int, int, int, TaskState::State);

    bool isConnected();

private:
    afqt::QThreadClientUp   m_qThreadClientUpdate;
    afqt::QThreadClientSend m_qThreadSend;
    Waves::Ptr push(Waves::Ptr);
    
    std::string task_output_body;
    bool wait_task_stdout;
    bool m_connected;

    size_t user_id;
    std::string user_name;

    af::Msg* msg_monitor_id;

};

}
#endif
