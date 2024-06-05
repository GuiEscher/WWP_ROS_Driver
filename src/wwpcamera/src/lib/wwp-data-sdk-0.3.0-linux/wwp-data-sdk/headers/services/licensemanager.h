#ifndef LICENSEMANAGER_H
#define LICENSEMANAGER_H

#ifndef WIN32
#include <unistd.h>
#include <pwd.h>

#endif
#include <sys/types.h>
#include <string>
#include <boost/asio.hpp>
//#include <boost/random.hpp>
//#include <boost/filesystem.hpp>

// in seconds
#define TRIAL_LENGTH 60*60*24*14

namespace wtl
{
    /**
     * @brief The AuthState enum
     * @details Authentification state of SDk
     */
    enum class AuthState
    {
        /**
          * @brief No license number activated
          */
        NotActivated,
        /**
          * @brief License number fully activated
          */
        FullActivated,
        /**
          * @brief Trial license number activated.
          */
        TrialActivated,
        /**
          * @brief Trial licence number expired.
          */
        TrialExpired,
        /**
          * @brief Wrong serial number provided.
          */
        WrongSN,
        /**
          * @brief ID of current computer already uses other license number.
          */
        ComputerAlreadyUsed,
        /**
          * @brief License number already assigned to other computerID.
          */
        AlreadyUsed
    };
    /**
    * @brief The LicenseManager class allow application to send network request and receive replies
    * @details Implemented using boost::asio library
    */
    class LicenseManager
    {
        std::shared_ptr<boost::asio::io_context> m_IoContext;
        std::unique_ptr<boost::asio::ip::tcp::resolver> m_Resolver;
        std::unique_ptr<boost::asio::ip::tcp::socket> m_Socket;
        std::string m_Host = "sw.workswell.cz";
        std::string m_Url = "/sdk_request.php";
        std::string m_DefaultDirPath;
        std::string m_DefaultDirLicensePath;
        std::string m_DefaultLicensePath;
        AuthState m_State = AuthState::NotActivated;

        bool m_Connected = false;
    public:
        /**
         * @brief LicenseManager
         */
        LicenseManager();
        /**
         * @brief
         */
        ~LicenseManager();
        /**
         * @brief LicenseManager
         * @param x
         */
        LicenseManager(const LicenseManager & x) = delete;
        /**
         * @brief operator =
         * @param x
         * @return
         */
        LicenseManager & operator=(const LicenseManager & x) = delete;
        /**
         * @brief Authenticate before every usage of WT-lib
         * @details Check license file, if no file exists, activation is required
         */
        wtl::AuthState authentificate(const std::string & computerID);
        /**
         * @brief activate
         * @param computerID
         * @param licenseNumber
         * @return
         */
        bool activate(const std::string & computerID, const std::string & licenseNumber);
        /**
         * @brief deactivate
         * @param computerID
         * @param licenseNumber
         * @return
         */
        bool deactivate(const std::string & computerID);
        /**
         * @brief Activate trial for 15 days
         * @param computerID
        */
        bool requestTrial(const std::string & computerID, const std::string & licenseNumber);
        /**
         * @brief Get current authentification state
         */
        wtl::AuthState getAuthState() const;
        /**
          *
          */
        bool licenseFileExists() const;
    private:
        void connect();
        void disconnect();
        int write(const uint8_t *buffer, std::size_t size) const;
        int write(const std::string &buffer) const;
        bool writeToLicenseFile(const std::string & answer, const std::string & computerID, const std::string & licenseNumber);
        bool checkLicenseFile(const std::string & computerID);
        bool parseLicenseFile(std::string & res, int option);
        int readUntil(std::string &buffer, char delim = ';', std::chrono::steady_clock::duration timeout = std::chrono::seconds(10)) const;
        bool runFor(std::chrono::steady_clock::duration timeout) const;
        bool sendRequest(const std::string & requestedParams, std::string & answer) const;
        std::string getRandomString(int len) const;
        std::string encrypt(const std::string & str) const;
        std::string decrypt(const std::string & str) const;
    };
}
#endif // LicenseManager_H
