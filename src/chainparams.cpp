// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2019 The Byron developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x00000b710c7c656f9a126394c67a7c50e8b570fc993c61de7fbaaf1ef850c2ba"))
    (30, uint256("0x0000016a5da3b714af5b5d50f1f04d25fdfa1e63bd2033480388c1f9f79dc2d5"))
    (10000, uint256("0xabbd14a9de1e2b7d149f1dfb29eed61590942fe23e95ae44b9e9e18e588f0fb1"))
    (15000, uint256("0x3f90fed782a6ba95370ac96204c36b9d187d17aee3694d53f295d684ba66a4ca"))
    (20000, uint256("0xe1ba86ac38f5745c950c4e65dae7a97c92a4f8a91f9b86e880726a57d869b091"))
    (25000, uint256("0x810e9c7c31f027e5c0b6a7b4746a3e2584f85e74567852f5a46b1af920bf6a43"))
    (30000, uint256("0x315cf9a6c9c67bd9a1b08fd3f99dd4bafc9cc5fc42bec05154368c5c5dfa5c15"))
    (31000, uint256("0x2e483f48f1038b040cff7712a250a89bbd97cdf5314b5355069468f677aa6011"))
    (32000, uint256("0x3125691213d3b04296f14f95762d3fb92576f27098d6fbd7b3210368da64a520"))
    (33000, uint256("0x906158a355911c87dd2fc5129c9a65995ae6e329cb134f7de19c0e1a9220566a"))
    (34000, uint256("0x79d286e54cdf765a0b6b879d548f488218ae35f3f3a263ee91ddfe5d27b29d5f"))
    (35000, uint256("0x2363f4d42c994349152cef79d5f4c15bab53778234f5defeecd39d3503de149e"))
    (36000, uint256("0x1d5551412fdd2612d06247ef8295196453f9505da113c68944449fc9c1a39b32"))
    (36931, uint256("0x07a2f37676919c8d5d794f5577f3eec5d2de9eedc9634523b1f0dbde0e5da91d"))
    (90000, uint256("0x50d14dbaa77a2591e24994244b19b90669bff3d076e0197a862ed3462adbe221"))
    (100000, uint256("0xf0e5c7c39b711ed46dcc325b59cd81b1b182a05016751ddee888617cc2fdeee7"))
    (155555, uint256("0x4ccc4230c7d292816875a390255b272337e4d27e0cfae9ed2f6712a16d2a7a9e"))
    (160000, uint256("0x28293ffd7dd11181182638478efcf5197088e83a7df72ca6d49702782c7f8c66"))
    (166666, uint256("0x2c0289f5a328a3641359a9273402e924734f123642e76f5637aab0d5287dd76d"))
    (176725, uint256("0x63ea73c1e681205d056d23f430877290d1303d2459f5621764da669b0acf646b"))
    (201000, uint256("0xa98a1571f58d7b6d5292e3e203230d75e891a7722fee17411308bd1ce013c3f4"))
    (220000, uint256("0xbb3155dd1ef3d31dc8382289be6fa42880d7efc25dc327a0c91886ca0fb00ac9")) 
    (248772, uint256("0xa4290d3091091336e6e715d53b2b1dbed07e63a190746e7f32439c908998b51d"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1591510917, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1570470324,
    0,
    250
};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1570470444,
    0,
    100
};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x11;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xfd;
        pchMessageStart[3] = 0x1a;
        vAlertPubKey = ParseHex("04bc9f12c91b66060847f1d67d17d79318e559230ce12d21732f9bc903b361f9f2026f759d4a4abe6f31edb5ba71275c9cd8408ffd7d88cd8772ed7aa075f3dd0e");
        nDefaultPort = 27215;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // BYRON starting difficulty is 1 / 2^12
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // BYRON: 1 day
        nTargetSpacing = 1 * 60;  // BYRON: 1 minute
        nMaturity = 80;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 1000;
        nModifierUpdateBlock = 100;
        nEnforceNewSporkKey = 1591510917;
        nRejectOldSporkKey = 1591510917;

        const char* pszTimestamp = "Enjoy to the crypto revolution Byron 7 may 2020";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 250 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0466f8e042492f7e1be50f8fa84bc2d39d0cea242704d219bc6d9cd7d1e20c4abc105e45b0510396978c22a7e9f35d21d6fb10005fc27febc2851ba4f051411865") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1591510917;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 306991;

        hashGenesisBlock = genesis.GetHash();


        assert(hashGenesisBlock == uint256("0x00000b710c7c656f9a126394c67a7c50e8b570fc993c61de7fbaaf1ef850c2ba"));
        assert(genesis.hashMerkleRoot == uint256("0xec01c0db9df7e01b39f6647c44bd5d306e1aa1744384d7cf86132beac1a4b5cf"));

        vFixedSeeds.clear();
        vSeeds.push_back(CDNSSeedData("cdseed1", "byron-seed1.coindroid.org"));
        vSeeds.push_back(CDNSSeedData("cdseed2", "byron-seed2.coindroid.org"));
        vSeeds.push_back(CDNSSeedData("cdseed3", "byron-seed3.coindroid.org"));
        vSeeds.push_back(CDNSSeedData("cdseed4", "byron-seed4.coindroid.org"));
        vSeeds.push_back(CDNSSeedData("cdseed5", "byron-seed5.coindroid.org"));
        vSeeds.push_back(CDNSSeedData("cdseed6", "byron-seed6.coindroid.org"));
        vSeeds.push_back(CDNSSeedData("cdseed7", "byron-seed7.coindroid.org"));                        

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 26);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 6);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 46);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true; // Default true
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false; // Default false
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "045a106cf3aea6d708df936467360a0d8e77dfa08b8e08233d3852de4752ec6a352296b80e7df6949a70ba34efcd5ab0b4ebea9a9b47649c2d32f3eda2010d9564";
        strSporkKeyOld = "048f591acbc42b77ab04aef7b010d6e23a0f1d4625c94a048e31d379f1a468b9534a8010f751f6bd30e4a9ba262ea8ed09f754f841d448c40a1a6866842cc005ca";
        strObfuscationPoolDummyAddress = "BWiAhFSVohoo7fSZ1rS5LdsFNcyZ3PAKQ3";
        nStartMasternodePayments = 1591510917;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xd0;
        pchMessageStart[1] = 0xcd;
        pchMessageStart[2] = 0xa9;
        pchMessageStart[3] = 0x96;
        vAlertPubKey = ParseHex("047702b6eb08ee32cfbd0cec8197e7287bc46aa3b9b855f268378a8e217eb1f7232dbca8f4e3459758ac2fd476a41266d8ce4ee19e3cacd5169802a9715bf572d1");
        nDefaultPort = 31244;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // BYRON: 1 day
        nTargetSpacing = 1 * 60;  // BYRON: 1 minute
        nLastPOWBlock = 100;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 101; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nEnforceNewSporkKey = 1521604800; //!> Sporks signed after Wednesday, March 21, 2018 4:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1522454400; //!> Reject old spork key after Saturday, March 31, 2018 12:00:00 AM GMT

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1570470324;
        genesis.nNonce = 1248594;

        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x0000031593b789b24efaa72a802fcc582f973d1d8871fb888dad1a951d0f1d57"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet byron addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet byron script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet byron BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet byron BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet byron BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04A8B319388C0F8588D238B9941DC26B26D3F9465266B368A051C5C100F79306A557780101FE2192FE170D7E6DEFDCBEE4C8D533396389C0DAFFDBC842B002243C";
        strSporkKeyOld = "04348C2F50F90267E64FACC65BFDC9D0EB147D090872FB97ABAE92E9A36E6CA60983E28E741F8E7277B11A7479B626AC115BA31463AC48178A5075C5A9319D4A38";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x93;
        pchMessageStart[1] = 0x9f;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xd8;
        nSubsidyHalvingInterval = 150;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // BYRON: 1 day
        nTargetSpacing = 1 * 60;        // BYRON: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;

        genesis.nTime = 1570470444;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 1;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 31246;
        //assert(hashGenesisBlock == uint256("0x55db4c46c531d7399537de526d10fddf1a36fbd7b270c721f0cd1a5e99743881"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 31248;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
