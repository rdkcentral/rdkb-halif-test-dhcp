/*
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2023 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# */

/**
* @file test_l1_dhcpv4c_api.c
* @page dhcpv4c_api Level 1 Tests
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios).
* This is to ensure that the dhcpv4c_api APIs meet the requirements across all vendors.
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None @n@n
*
* Ref to API Definition specification documentation : [DHCPv4ChalSpec.md](../../../docs/pages/DHCPv4ChalSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include <sys/socket.h>
#include "dhcpv4c_api.h"
#include <netinet/in.h> // for inet_aton
#include <arpa/inet.h>  // for htonl and ntohl

static int gTestGroup = 1;
static int gTestID = 1;

struct in_addr addr;


/**
* @brief Test case to verify the functionality of dhcpv4c_get_ert_lease_time function
*
* This test case verifies the functionality of the dhcpv4c_get_ert_lease_time function by checking if the return value is STATUS_SUCCESS.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 001 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :--------------: | ----------- | --------- | --------------- | ----- |
* |  01  |Invoking dhcpv4c_get_ert_lease_time with valid memory location| *pValue = valid pointer | STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_lease_time(void)
{
    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    UINT value = 0;
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_lease_time...");
    status = dhcpv4c_get_ert_lease_time(&value);

    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Return value: %u", value);
    // Check if the return value is STATUS_SUCCESS
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test is to check the behavior of DHCPv4 API when given an invalid pointer
*
* This test checks whether the DHCPv4 API dhcpv4c_get_ert_lease_time correctly handles the case when an invalid pointer is passed as input.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 002 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 |Invoking dhcpv4c_get_ert_lease_time with NULL | pValue = NULL  | STATUS_FAILURE | Should fail with STATUS_FAILURE |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_lease_time(void)
{
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_lease_time with NULL pointer...");
    status = dhcpv4c_get_ert_lease_time(NULL);
    UT_LOG_DEBUG("Return status: %d", status);
    // Check if the return value is STATUS_FAILURE
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the functionality of dhcpv4c_get_ert_remain_lease_time function when a valid pointer is passed as an argument.
*
* This test is for verifying the functionality of the dhcpv4c_get_ert_remain_lease_time function. It checks if the function returns STATUS_SUCCESS when a valid pointer is passed as an argument. It also verifies if the lease time is within the valid range.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 003 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_remain_lease_time with a valid pointer | *pValue = valid pointer | STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_remain_lease_time(void)
{
    gTestID = 3;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    UINT leaseTime = 0;
    int status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_remain_lease_time with a valid pointer");
    status = dhcpv4c_get_ert_remain_lease_time(&leaseTime);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Lease Time: %u", leaseTime);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test case is used to verify the behavior of the function dhcpv4c_get_ert_remain_lease_time when provided with a NULL pointer.
*
* The objective of this test is to ensure that the function returns STATUS_FAILURE when invoked with a NULL pointer as the input argument.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 004 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_remain_lease_time with a NULL pointer |pValue = NULL | STATUS_FAILURE | Should be successful |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_remain_lease_time(void)
{
    gTestID = 4;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    int status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_remain_lease_time with a NULL pointer");
    status = dhcpv4c_get_ert_remain_lease_time(NULL);
    UT_LOG_DEBUG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test is to verify the functionality of the dhcpv4c_get_ert_remain_renew_time API when a valid memory address is passed.
*
* The API is tested to ensure that it returns the remaining renew time correctly and that the value is within the valid range.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 005 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_remain_renew_time with valid memory address for pValue. | Value = valid memory address |STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_remain_renew_time(void)
{
    gTestID = 5;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    UINT value = 0;
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_remain_renew_time with valid memory address for pValue.");
    status = dhcpv4c_get_ert_remain_renew_time(&value);

    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Return value: %u", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test is to verify the functionality of the dhcpv4c_get_ert_remain_renew_time API when provided with a NULL pointer.
*
* The objective of this test is to verify the behavior of the function dhcpv4c_get_ert_remain_renew_time when a NULL pointer is passed as the input parameter.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 006 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_remain_renew_time with NULL pointer for pValue. | pValue = NULL |  STATUS_FAILURE | Should be unsuccessful |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_remain_renew_time(void)
{
    gTestID = 6;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_remain_renew_time with NULL pointer for pValue.");
    status = dhcpv4c_get_ert_remain_renew_time(NULL);
    UT_LOG_DEBUG("Return value: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test case is used to validate the dhcpv4c_get_ert_remain_rebind_time API.
*
* The objective of this test is to verify whether the DHCPv4 client API dhcpv4c_get_ert_remain_rebind_time
* correctly returns the remaining rebind time in the Extended Rebinding Time option (ERT) in DHCPv4 messages.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 007 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_remain_rebind_time with valid pValue pointer. | Value = valid memory address | STATUS_SUCCESS |  Should be successful |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_remain_rebind_time(void)
{
    gTestID = 7;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    UINT timeValue = 0;
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_remain_rebind_time with valid pValue pointer.");
    status = dhcpv4c_get_ert_remain_rebind_time(&timeValue);

    UT_LOG_DEBUG("Return Status: %d", status);
    UT_LOG_DEBUG("Return value: %u", timeValue);
    // Check the return status and time value
    UT_ASSERT_EQUAL(STATUS_SUCCESS, status);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test case to validate the function dhcpv4c_get_ert_remain_rebind_time, when a NULL pValue pointer is passed.
*
* This test case is used to verify the behavior of dhcpv4c_get_ert_remain_rebind_time function when NULL pValue pointer is passed as an argument. It checks whether the function correctly handles the NULL pointer and returns the expected failure status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 008 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_remain_rebind_time with NULL pValue pointer | pValue = NULL | STATUS_FAILURE | Should return the expected failure status |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_remain_rebind_time(void)
{
    gTestID = 8;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    UINT *pValue = NULL;
    INT status = 0;

    // Invalid pValue pointer
    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_remain_rebind_time with NULL pValue pointer.");
    status = dhcpv4c_get_ert_remain_rebind_time(pValue);

    UT_LOG_DEBUG("Return Status: %d", status);

    // Check the return status
    UT_ASSERT_EQUAL(STATUS_FAILURE, status);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test case verifies the successful execution of the function dhcpv4c_get_ert_config_attempts when a valid pointer is passed as a parameter.
*
* In this test case, the dhcpv4c_get_ert_config_attempts function is called with a valid pointer (someInteger) to retrieve
* the number of attempts made by the DHCPv4 client to get the ERT configuration.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 009 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_config_attempts with pValue = &someInteger | *pValue = valid pointer | STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_config_attempts(void)
{
    gTestID = 9;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT someInteger = 0;
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_config_attempts with pValue = &someInteger");
    status = dhcpv4c_get_ert_config_attempts(&someInteger);
    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Return value: %d", someInteger);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test case to verify the behavior of dhcpv4c_get_ert_config_attempts API when a NULL pointer is passed as the argument.
*
* This test validates that the dhcpv4c_get_ert_config_attempts API returns an appropriate status
* and the value of the pointer remains unchanged when a NULL pointer is passed as the argument.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 010 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01| Invoking dhcpv4c_get_ert_config_attempts with NULL pointer | pValue = NULL | STATUS_FAILURE| Should be unsuccessful |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_config_attempts(void)
{
    gTestID = 10;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT *pValue = NULL;
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_config_attempts with pValue = NULL");
    status = dhcpv4c_get_ert_config_attempts(pValue);

    UT_LOG_DEBUG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to validate if the memory location for pName is valid
*
* This test checks if the memory location for pName is valid and can be accessed by the DHCPv4c API.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 011 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_ifname with Valid memory location| pName = valid buffer | STATUS_SUCCESS | should return STATUS_SUCCESS|
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_ifname(void)
{
    gTestID = 11;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    int status = 0;
    CHAR pName[64] = {0};

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_ifname with a valid memory location");
    status = dhcpv4c_get_ert_ifname(pName);

    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Return value : %s ", pName);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test case to verify the behavior when a NULL pointer is passed for the pName parameter in the dhcpv4c_get_ert_ifname API.
*
* This test case checks whether the API returns a failure status when a NULL pointer is passed for the pName parameter.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 012 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_ifname with null pointer for pName | pName = NULL |STATUS_FAILURE | Should fail |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_ifname(void)
{
    gTestID = 12;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    CHAR *pName = NULL;
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_ifname with null pointer for pName");
    status = dhcpv4c_get_ert_ifname(pName);

    UT_LOG_DEBUG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test case verifies the successful execution of the function dhcpv4c_get_ert_fsm_state when a valid pointer is passed as a parameter.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 013 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_fsm_state with valid pointer | Invoke dhcp4c_get_ert_ifname with pValue as NULL | STATUS_SUCCESS | Should return STATUS_SUCCESS |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_fsm_state(void)
{
    gTestID = 13;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT value = 0;
    int status = 0;

    // Allocate memory location
    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_fsm_state() with valid memory location...");
    // Call dhcpv4c_get_ert_fsm_state()
    status = dhcpv4c_get_ert_fsm_state(&value);

    // Check the return status and the value of pValue

    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Return value: %d", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test case checks for the negative scenario when NULL pointer is provided as an argument to dhcpv4c_get_ert_fsm_state() function.
*
* This test case verifies that the function dhcpv4c_get_ert_fsm_state() returns STATUS_FAILURE when a NULL pointer is provided as an argument.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 014 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | --------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_fsm_state() with NULL pointer | pValue = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_fsm_state(void)
{
    gTestID = 14;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    int status = 0;

    // Call dhcpv4c_get_ert_fsm_state() with NULL pointer
    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_fsm_state() with NULL pointer...");
    status = dhcpv4c_get_ert_fsm_state(NULL);
    UT_LOG_DEBUG("Return status: %d", status);
    // Check the return status
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test case to verify the functionality of dhcpv4c_get_ert_ip_addr function
*
* This test case verifies dhcpv4c_get_ert_ip_addr function by passing a valid memory location to pValue argument and checking the return status and the IP address range.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 015 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_ip_addr with valid memory location for pValue | *pValue = valid pointer | STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_ip_addr(void)
{
    gTestID = 15;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    char ip_str[20] = {0};
    UINT ipAddr = 0;
    INT status = 0;

    /* Test with a valid memory location as the pValue argument */
    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_ip_addr with valid memory location for pValue");
    status = dhcpv4c_get_ert_ip_addr(&ipAddr);

    /* Test description */
    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Return value before modification : %u", ipAddr);
    /* Verify return status */
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    addr.s_addr = ipAddr ;
    strcpy(ip_str,inet_ntoa(addr));

    UT_LOG_DEBUG("Return value: %s", ip_str);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test function verifies the behavior of the dhcpv4c_get_ert_ip_addr() API when invoked with a null pointer for the pValue argument.
*
* The dhcpv4c_get_ert_ip_addr() function is tested to ensure that it correctly handles the case when a null pointer is passed as the pValue argument. This test is important to validate the error handling capability of the API and ensure that it does not cause any unexpected behavior or crashes when invoked with invalid input.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 016 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_ip_addr with null pointer for pValue | pValue = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_ip_addr(void)
{
    gTestID = 16;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_ip_addr with null pointer for pValue");
    /* Test with a null pointer for pValue argument */
    status = dhcpv4c_get_ert_ip_addr(NULL);

    /* Test description */
    UT_LOG_DEBUG("Return status: %d", status);
    /* Verify return status */
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test case validates the positive scenario for the dhcpv4c_get_ert_mask() API.
*
* In this test case, the dhcpv4c_get_ert_mask() API is invoked with valid pValue and the result is verified.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 017 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01  | Invoke dhcpv4c_get_ert_mask API with valid pValue | pValue = valid buffer | STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_mask(void)
{
    gTestID = 17;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    UINT value = 0;
    INT status = 0;

    // Invoke API
    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_mask with valid pValue...");
    status = dhcpv4c_get_ert_mask(&value);

    // Verify result
    UT_LOG_DEBUG("Return Status: %d", status);
    UT_LOG_DEBUG("Output: pValue = %u", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies that the function dhcpv4c_get_ert_mask returns STATUS_FAILURE when the pValue pointer is NULL.
*
* This test case is part of the Basic test group and has a high priority. It tests the functionality of the dhcpv4c_get_ert_mask API when the pValue pointer is NULL. The objective is to ensure that the API returns STATUS_FAILURE in this scenario.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 018 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_mask when pValue pointer is NULL | pValue = NULL | STATUS_FAILURE | Should fail with STATUS_FAILURE |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_dhcpv4c_get_ert_mask(void)
{
    gTestID = 18;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    UINT *pValue = NULL;
    INT status = 0;

    // Test input
    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_mask with NULL pValue pointer...");
    // Invoke API
    status = dhcpv4c_get_ert_mask(pValue);

    // Verify result
    UT_LOG_DEBUG("Return Status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test case is used to verify the functionality of the dhcpv4c_get_ert_gw function.
*
* This test case checks whether the dhcpv4c_get_ert_gw function returns the expected status and value when provided with a valid memory location for pValue.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 019 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_gw with valid memory location for pValue | *pValue = valid pointer | STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_gw(void)
{
    gTestID = 19;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    UINT value = 0;
    char ip_str[20] = {0};
    INT status = 0;

    // Provide a valid memory location for pValue
    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_gw with valid memory location for pValue");
    status = dhcpv4c_get_ert_gw(&value);

    // Check the return status
    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Return value: %u", value);
    UT_ASSERT_EQUAL(STATUS_SUCCESS, status);
    addr.s_addr = value ;
    strcpy(ip_str,inet_ntoa(addr));

    UT_LOG_DEBUG("Return value after modification: %s", ip_str);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the behavior of dhcpv4c_get_ert_gw function when provided with NULL pointer for pValue.
*
* This test case checks if the dhcpv4c_get_ert_gw function returns STATUS_FAILURE when invoked with a NULL pointer for pValue as input.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 020 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_gw with NULL pointer | pValue = NULL | STATUS_FAILURE | The dhcpv4c_get_ert_gw function should return STATUS_FAILURE |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_gw(void)
{
    gTestID = 20;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_gw with NULL pointer for pValue");
    // Provide NULL pointer for pValue
    status = dhcpv4c_get_ert_gw(NULL);

    // Check the return status
    UT_LOG_DEBUG("Return status: %d", status);
    UT_ASSERT_EQUAL(STATUS_FAILURE, status);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test case to verify the successful retrieval of DNS servers in DHCPv4c API
*
* This test case verifies the functionality of the dhcpv4c_get_ert_dns_svrs API to retrieve DNS servers. It checks whether the API returns the correct status and retrieves the IP addresses successfully.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 021 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_dns_svrs with valid memory for dhcpv4c_ip_list_t | ip_list = valid pointer to structure dhcpv4c_ip_list_t| STATUS_SUCCESS | Should be successful  |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_dns_svrs(void)
{
    gTestID = 21;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dhcpv4c_ip_list_t ip_list;
    INT status = 0;

    memset(&ip_list, 0, sizeof(dhcpv4c_ip_list_t));
    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_dns_svrs with valid memory for dhcpv4c_ip_list_t");
    status = dhcpv4c_get_ert_dns_svrs(&ip_list);

    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Number of IP addresses: %d", ip_list.number);
    UT_LOG_DEBUG("First IP address: %u.%u.%u.%u", ip_list.addrs[0], ip_list.addrs[1], ip_list.addrs[2], ip_list.addrs[3]);

    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test case to check for invalid memory for dhcpv4c_ip_list_t
*
* This test case verifies the behavior of the dhcpv4c_get_ert_dns_svrs API when invoked with an invalid memory for the dhcpv4c_ip_list_t structure.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 022 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | --------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_dns_svrs with null pointer | pList = NULL | STATUS_FAILURE | Should return a failure status |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_dns_svrs(void)
{
    gTestID = 22;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dhcpv4c_ip_list_t *pList = NULL;
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_dns_svrs with null pointer");
    status = dhcpv4c_get_ert_dns_svrs(pList);
    UT_LOG_DEBUG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test case to validate the behavior of dhcpv4c_get_ert_dhcp_svr function when a valid memory address is provided
*
* This test case verifies the functionality of the dhcpv4c_get_ert_dhcp_svr function when a valid memory address is passed as an argument.
* The objective of this test is to confirm that the function returns the expected output value and the return status indicates success.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 023 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_dhcp_svr with valid memory address provided | *pValue = valid memory location | STATUS_SUCCESS | Function call should succeed |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_dhcp_svr(void)
{
    gTestID = 23;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    char ip_str[20] = {0};
    UINT value = 0;
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_dhcp_svr with valid memory address provided");
    status = dhcpv4c_get_ert_dhcp_svr(&value);
    UT_LOG_DEBUG("Return Status: %d", status);
    UT_LOG_DEBUG("Output Value: %u", value);

    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    addr.s_addr = value;
    strcpy(ip_str,inet_ntoa(addr));

    UT_LOG_DEBUG("Return value after modification: %s", ip_str);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test case to verify the behavior when a null pointer is provided to the dhcpv4c_get_ert_dhcp_svr API.
*
* This test case verifies if the API can handle the scenario where a null pointer is provided as the input to the dhcpv4c_get_ert_dhcp_svr API. The API is expected to return a failure status in such cases.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 024 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n.
* **Dependencies:** None @n.
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 |Invoking dhcpv4c_get_ert_dhcp_svr with NULL  | pValue = NULL |STATUS_FAILURE | Should fail with STATUS_FAILURE |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_dhcp_svr(void)
{
    gTestID = 24;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ert_dhcp_svr with null pointer provided");
    status = dhcpv4c_get_ert_dhcp_svr(NULL);
    UT_LOG_DEBUG("Return Status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test the API dhcpv4c_get_ecm_lease_time with valid pValue
*
* This test case checks the functionality of dhcpv4c_get_ecm_lease_time API when called with a valid pValue. It verifies that the correct
* output value is returned and the return status is success.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 025 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* |:----:|--------------|-----------|----------------|------|
* | 01 | Invoking dhcpv4c_get_ecm_lease_time with valid pValue | *pValue = valid memory location | STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_lease_time(void)
{
    gTestID = 25;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    UINT value = 0;
    INT result = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_lease_time with valid pValue");
    result = dhcpv4c_get_ecm_lease_time(&value);

    UT_LOG_DEBUG("Return Status: %d", result);
    UT_LOG_DEBUG("Output Value: %u", value);

    UT_ASSERT_EQUAL(result, STATUS_SUCCESS);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test case validates the behavior of dhcpv4c_get_ecm_lease_time when pValue is NULL.
*
* The objective of this test is to ensure that the function dhcpv4c_get_ecm_lease_time returns STATUS_FAILURE when pValue is NULL.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 026 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :-----: | ----------- | --------- | --------------- | ----- |
* |    01   | Invoking dhcpv4c_get_ecm_lease_time with NULL pointer | pValue = NULL | STATUS_FAILURE | Should be unsuccessful |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_lease_time(void)
{
    gTestID = 26;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT result = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_lease_time with NULL pValue");
    result = dhcpv4c_get_ecm_lease_time(NULL);
    UT_LOG_DEBUG("Return Status: %d", result);
    UT_ASSERT_EQUAL(result, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test case to verify the functionality of dhcpv4c_get_ecm_remain_lease_time API.
*
* This test case is used to verify the functionality of dhcpv4c_get_ecm_remain_lease_time API by invoking the API with a valid pointer and checking the return value and the retrieved lease time.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 027 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ecm_remain_lease_time with a valid pointer | *pValue = valid memory location | STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_remain_lease_time(void)
{
    gTestID = 27;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    UINT value = 0;
    INT status = 0;

    // Invoke the API with a valid pointer
    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_remain_lease_time with a valid pointer...");
    status = dhcpv4c_get_ecm_remain_lease_time(&value);

    // Check the return value and the retrieved lease time
    UT_LOG_DEBUG("Returned status: %d", status);
    UT_LOG_DEBUG("Retrieved lease time: %u", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test the API dhcpv4c_get_ecm_remain_lease_time with a null pointer.
*
* This test case verifies the behavior of the function dhcpv4c_get_ecm_remain_lease_time when called with a null pointer as the input argument. It checks if the function return value is equal to STATUS_FAILURE.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 028 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke the API with a null pointer | pValue = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_remain_lease_time(void)
{
    gTestID = 28;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;

    // Invoke the API with a null pointer
    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_remain_lease_time with a null pointer...");
    status = dhcpv4c_get_ecm_remain_lease_time(NULL);

    // Check the return value
    UT_LOG_DEBUG("Returned status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This function tests the functionality of dhcpv4c_get_ecm_remain_renew_time API by checking the return status and value of pValue for the default case.
*
* This test verifies the behavior of dhcpv4c_get_ecm_remain_renew_time API by checking the return status and value of pValue for the default input case.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 029 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :------: | ----------- | --------- | --------------- | ----- |
* | 01 |Invoke dhcpv4c_get_ecm_remain_renew_time with valid memory  | *pValue = valid memory location | STATUS_SUCCESS | |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_remain_renew_time(void)
{
    gTestID = 29;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    UINT value = 0;
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_remain_renew_time with a valid memory location");
    status = dhcpv4c_get_ecm_remain_renew_time(&value);
    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Return value: %u", value);
    // Check the return status
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test is used to verify the behavior of the dhcpv4c_get_ecm_remain_renew_time function when a NULL pointer is passed as input.
*
* The objective of this test is to ensure that the dhcpv4c_get_ecm_remain_renew_time function returns a STATUS_FAILURE when a NULL pointer is passed as input.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 030 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ecm_remain_renew_time with NULL | pValue = NULL | STATUS_FAILURE | Should be unsuccessful |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_remain_renew_time(void)
{
    gTestID = 30;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcp4c_get_ert_lease_time with NULL");
    status = dhcpv4c_get_ecm_remain_renew_time(NULL);
    UT_LOG_DEBUG("Return status: %d", status);

    // Check the return status
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test case to verify the functionality of dhcpv4c_get_ecm_remain_rebind_time API with valid pValue.
*
* This test case verifies the functionality of dhcpv4c_get_ecm_remain_rebind_time API with valid pValue. It checks if the API returns the expected status and value.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 031 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ecm_remain_rebind_time with valid pValue | *pValue = valid memory location | STATUS_SUCCESS | |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_ecm_remain_rebind_time(void)
{
    gTestID = 31;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    UINT value = 0;
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_remain_rebind_time with valid pValue.");
    status = dhcpv4c_get_ecm_remain_rebind_time(&value);

    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Return pValue: %u", value);

    UT_ASSERT_EQUAL(STATUS_SUCCESS, status);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test case to verify the behavior of dhcpv4c_get_ecm_remain_rebind_time
*
* This function tests the behavior of dhcpv4c_get_ecm_remain_rebind_time when a null pointer is passed as the value argument.
* It verifies whether the function returns STATUS_FAILURE as expected.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 032 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :---: | --------- | ---------- | ------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ecm_remain_rebind_time with NULL pointer | pValue = NULL | STATUS_FAILURE | The function should return STATUS_FAILURE |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_remain_rebind_time(void)
{
    gTestID = 32;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_remain_rebind_time with NULL pValue.");
    status = dhcpv4c_get_ecm_remain_rebind_time(NULL);
    UT_LOG_DEBUG("Return status: %d", status);
    UT_ASSERT_EQUAL(STATUS_FAILURE, status);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the functionality of the 'dhcpv4c_get_ecm_config_attempts' API with a valid pointer.
*
* This test verifies the functionality of the 'dhcpv4c_get_ecm_config_attempts' API by invoking it with a valid pointer and validating the return value and the obtained value.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 033 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
*
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking 'dhcpv4c_get_ecm_config_attempts' API with valid pointer | *pValue = valid memory location | STATUS_SUCCESS | The return value should be STATUS_SUCCESS |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_config_attempts(void)
{
    gTestID = 33;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT value = 0;
    INT ret = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_config_attempts with valid pointer");
    ret = dhcpv4c_get_ecm_config_attempts(&value);
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_LOG_DEBUG("Return value: %d", value);
    UT_ASSERT_EQUAL(ret, STATUS_SUCCESS);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test validates the behavior of the dhcpv4c_get_ecm_config_attempts API when a NULL pointer is passed as argument.
*
* In this test, the dhcpv4c_get_ecm_config_attempts API is invoked with a NULL pointer as argument. The objective is to validate that the API returns STATUS_FAILURE when a NULL pointer is passed.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 034 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via the console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ecm_config_attempts with NULL pointer | pValue = NULL | STATUS_FAILURE | Should be unsuccessful |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_ecm_config_attempts(void)
{
    gTestID = 34;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT *pValue = NULL;
    INT ret = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_config_attempts with NULL pointer");
    ret = dhcpv4c_get_ecm_config_attempts(pValue);
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL(ret, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test case to validate if the dhcpv4c_get_ecm_ifname function returns STATUS_SUCCESS when a valid memory location is passed as an argument.
*
* This test case checks the behavior of the dhcpv4c_get_ecm_ifname function when a valid memory location is provided as an argument.
* The expected result of this test is that the function should return STATUS_SUCCESS.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 035 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoke the dhcpv4c_get_ecm_ifname function with a valid memory location as the argument | pName = valid memory location | STATUS_SUCCESS | Should return STATUS_SUCCESS |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_ifname(void)
{
    gTestID = 35;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    CHAR pName[64] = {0};
    INT status = 0;

    // Allocate a 64-byte CHAR array
    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_ifname with pName as valid memory location. Expected Output: STATUS_SUCCESS");
    // Invoke the API
    status = dhcpv4c_get_ecm_ifname(pName);
    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Return value: %s", pName);
    // Check the return value
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test case validates the behavior of the dhcpv4c_get_ecm_ifname() function when a NULL pointer is passed as the argument.
*
* This test case checks whether the dhcpv4c_get_ecm_ifname() function correctly handles the NULL pointer argument and returns STATUS_FAILURE.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 036 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ecm_ifname with pName as NULL | pName = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_ifname(void)
{
    gTestID = 36;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_ifname with pName as NULL. Expected Output: STATUS_FAILURE");
    // Invoke the API with pName as NULL
    status = dhcpv4c_get_ecm_ifname(NULL);
    UT_LOG_DEBUG("Return status: %d", status);
    // Check the return value
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This function tests the dhcpv4c_get_ecm_fsm_state API.
*
* This test case checks whether the dhcpv4c_get_ecm_fsm_state API returns the expected status and updates the value between 1 and 6.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 037 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ecm_fsm_state | *pValue = valid memory location | STATUS_SUCCESS | Should be successful |
*/

void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_fsm_state(void)
{
    gTestID = 37;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT value = 0;
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_fsm_state with valid pointer");
    status = dhcpv4c_get_ecm_fsm_state(&value);
    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Return value: %d", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test case tests the negative scenario of the dhcpv4c_get_ecm_fsm_state API.
*
* The objective of this test is to verify the behavior of the dhcpv4c_get_ecm_fsm_state API when passed a NULL pointer for the value parameter.
*
* **Test Group ID:** Basic (for L1): 01
* **Test Case ID:** 038 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description  | Test Data  | Expected Result | Notes |
* | :--------: | --------- | ------------- | -------------- | ----------- |
* |  01  | Invoking dhcpv4c_get_ecm_fsm_state with pValue = NULL  | pValue = NULL | STATUS_FAILURE | Should fail with STATUS_FAILURE |
*
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_fsm_state(void)
{
    gTestID = 38;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT *pValue = NULL;
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_fsm_state with NULL");
    status = dhcpv4c_get_ecm_fsm_state(pValue);
    UT_LOG_DEBUG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test the functionality of the dhcpv4c_get_ecm_ip_addr function
*
* This test validates the dhcpv4c_get_ecm_ip_addr function by invoking it with a valid UINT pointer.
* It checks the status of the function call and the IP address returned by the function.
* The test ensures that the status is STATUS_SUCCESS .
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 039 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ecm_ip_addr with a valid UINT pointer | *pValue = valid memory location | STATUS_SUCCESS | The function call should be successful |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_ip_addr(void)
{
    gTestID = 39;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    char ip_str[20] = {0};
    UINT ipAddr = 0;
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_ip_addr with a valid UINT pointer.");
    status = dhcpv4c_get_ecm_ip_addr(&ipAddr);
    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Return value: %u", ipAddr);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    addr.s_addr = ipAddr ;
    strcpy(ip_str,inet_ntoa(addr));

    UT_LOG_DEBUG("Return value after modification: %s", ip_str);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for the function dhcpv4c_get_ecm_ip_addr to check negative case with null pointer.
*
* This test case checks the functionality of dhcpv4c_get_ecm_ip_addr function when a null pointer is passed as an argument. The objective of this test is to ensure that the function properly handles the null pointer and returns the expected status.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 040 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ecm_ip_addr with a null pointer | pValue = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_ip_addr(void)
{
    gTestID = 40;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_ip_addr with a null pointer.");
    status = dhcpv4c_get_ecm_ip_addr(NULL);
    UT_LOG_DEBUG("Status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test case is used to verify the functionality of the dhcpv4c_get_ecm_mask function when invoked with valid pValue.
*
* The objective of this test is to ensure that the dhcpv4c_get_ecm_mask function returns the correct status value and the expected value for pValue when invoked with valid input.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 041 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke the dhcpv4c_get_ecm_mask function with valid pValue | *pValue = valid memory location |  STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_mask(void)
{
    gTestID = 41;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    UINT value = 0;
    INT status = 0;

    /* Invoke the API with valid pValue */
    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_mask with valid pointer...");
    status = dhcpv4c_get_ecm_mask(&value);

    /* Verify the return status */
    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("pValue: %u", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    /* Log the end of the test */
    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test is used to verify the behavior of dhcpv4c_get_ecm_mask when invoked with a null pValue parameter.
*
* The purpose of this test is to ensure that the function dhcpv4c_get_ecm_mask handles the null pValue parameter correctly.
*
* Test Group ID: Basic: 01
* Test Case ID: 042 @n
* Priority: High
*
* Pre-Conditions: None
* Dependencies: None
* User Interaction: If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* Test Procedure:
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ecm_mask with a null pointer | pValue = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_mask(void)
{
    gTestID = 42;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;

    /* Invoke the API with null pValue */
    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_mask with null pValue...");
    status = dhcpv4c_get_ecm_mask(NULL);

    /* Verify the return status */
    UT_LOG_DEBUG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    /* Log the end of the test */
    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the functionality of dhcpv4c_get_ecm_gw when provided with valid output memory and to check the status
*
* This test verifies the functionality of dhcpv4c_get_ecm_gw when provided with valid output memory.
* The objective of this test is to check if the status returned by the API is STATUS_SUCCESS.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 043 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke dhcpv4c_get_ecm_gw with valid output memory | *pValue = valid memory location | STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_gw( void )
{
    gTestID = 43;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;
    UINT output = 0;
    char ip_str[20] = {0};

    // Prepare valid output memory
    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_gw with a valid memory location");
    // Invoke the API
    status = dhcpv4c_get_ecm_gw(&output);
    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Return value: %d", output);
    // Verify the status is STATUS_SUCCESS
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    addr.s_addr = output ;
    strcpy(ip_str,inet_ntoa(addr));

    UT_LOG_DEBUG("Return value after modification: %s", ip_str);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Tests the DHCPv4c_get_ecm_gw function when a null pointer is provided for the output memory
*
* This test case verifies the behavior of the DHCPv4c_get_ecm_gw function when a null pointer is provided for the output memory.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 044 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ecm_gw with NULL pointer | pValue = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_gw( void )
{
    gTestID = 44;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_gw with NULL");
    // Invoke the API with NULL as output memory pointer
    status = dhcpv4c_get_ecm_gw(NULL);
    UT_LOG_DEBUG("Return status: %d", status);
    // Verify the status is STATUS_FAILURE
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify if a valid memory location is provided to the API.
*
* This test case verifies whether the API 'dhcpv4c_get_ecm_dns_svrs' returns successfully when a valid memory location is provided.
*
* Test Group ID: Basic: 01 @n
* Test Case ID: 045 @n
* Priority: High @n@n
*
* Pre-Conditions: None @n
* Dependencies: None @n
* User Interaction: If the user chooses to run the test in interactive mode, then the test case has to be selected via console @n
*
* Test Procedure: @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ecm_dns_svrs with a valid memory location | pList = valid pointer to structure dhcpv4c_ip_list_t | STATUS_SUCCESS | The number of IP addresses should be between 1-4 |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_dns_svrs(void)
{
    gTestID = 45;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dhcpv4c_ip_list_t list;
    INT result = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_dns_svrs with a valid memory location");
    result = dhcpv4c_get_ecm_dns_svrs(&list);
    UT_LOG_DEBUG("Return status: %d", result);
    UT_ASSERT_EQUAL(result, STATUS_SUCCESS);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test case is used to verify the behavior of the dhcpv4c_get_ecm_dns_svrs function when a null pointer is passed for the pList parameter.
*
* The purpose of this test is to ensure that the correct error code is returned when a null pointer is passed as an argument to the function dhcpv4c_get_ecm_dns_svrs.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 046 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via the console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* |  01   | Invoking dhcpv4c_get_ecm_dns_svrs with NULL pointer  | pList = NULL | STATUS_FAILURE | Should be unsuccessful |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_dns_svrs(void)
{
    gTestID = 46;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT result = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_dns_svrs with NULL");
    result = dhcpv4c_get_ecm_dns_svrs(NULL);
    UT_LOG_DEBUG("Return status: %d", result);
    UT_ASSERT_EQUAL(result, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to ensure that the dhcpv4c_get_ecm_dhcp_svr function returns a valid IP address within the specified range when a valid pointer is provided.
*
* This test verifies that the dhcpv4c_get_ecm_dhcp_svr function returns a valid IP address within the specified range when a valid pointer is provided. It also checks the return status of the function.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 047 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke dhcpv4c_get_ecm_dhcp_svr with valid pointer |*pValue = valid memory location  | STATUS_SUCCESS  | Should be successful |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_dhcp_svr(void)
{
    gTestID = 47;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    char ip_str[20] = {0};
    UINT ipValue = 0;
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_dhcp_svr with valid pointer");
    status = dhcpv4c_get_ecm_dhcp_svr(&ipValue);
    UT_LOG_DEBUG("Return Status: %d", status);
    UT_LOG_DEBUG("Output: IP Address - %u",ipValue);

    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    addr.s_addr = ipValue ;
    strcpy(ip_str,inet_ntoa(addr));

    UT_LOG_DEBUG("Return value after modification: %s", ip_str);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test case checks the functionality of dhcpv4c_get_ecm_dhcp_svr API when NULL pointer is passed as input parameter.
*
* dhcpv4c_get_ecm_dhcp_svr API is tested in this test case to check if it handles NULL pointer gracefully and returns STATUS_FAILURE.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 048 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | ----- | --------- | -------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ecm_dhcp_svr with NULL pointer | pValue = NULL | STATUS_FAILURE | Should be unsuccessful |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_dhcp_svr(void)
{
    gTestID = 48;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_ecm_dhcp_svr with NULL pointer");
    status = dhcpv4c_get_ecm_dhcp_svr(NULL);
    UT_LOG_DEBUG("Return Status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test case is used to validate the dhcpv4c_get_emta_remain_lease_time API when invoked with a valid memory location.
*
* The purpose of this test is to ensure that the dhcpv4c_get_emta_remain_lease_time API returns the correct status and value when invoked with a valid memory location.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 049 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | -------------------- | --------------------- | ----- |
* | 01 | Invoking dhcpv4c_get_emta_remain_lease_time with valid memory location |*pValue = valid memory location | STATUS_SUCCESS | Status = STATUS_SUCCESS, value is greater than or equal to 0 and less than or equal to UINT_MAX - 1 |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_emta_remain_lease_time(void)
{
    gTestID = 49;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    UINT value = 0;
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_emta_remain_lease_time with valid memory location");
    status = dhcpv4c_get_emta_remain_lease_time(&value);
    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Output value: %u", value);

    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test the dhcpv4c_get_emta_remain_lease_time function with a NULL pointer.
*
* This test case verifies the behavior of the dhcpv4c_get_emta_remain_lease_time function when a NULL pointer is passed as the argument. The expected outcome is a STATUS_FAILURE return value.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 050 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via the console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :------: | ----------- | --------- | --------------- | ----- |
* | 01 | Invoking dhcpv4c_get_emta_remain_lease_time with NULL | pValue = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_emta_remain_lease_time(void)
{
    gTestID = 50;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_emta_remain_lease_time with NULL pointer");
    status = dhcpv4c_get_emta_remain_lease_time(NULL);
    UT_LOG_DEBUG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test the function dhcpv4c_get_emta_remain_renew_time()
*
* This test case verifies the functionality of the dhcpv4c_get_emta_remain_renew_time() API.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 051 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :--------------: | ----------- | --------- | --------------- | ----- |
* | 01 | Invoking dhcpv4c_get_emta_remain_renew_time with valid pValue| *pValue = valid memory location | STATUS_SUCCESS  | Should be successful |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_emta_remain_renew_time(void)
{
    gTestID = 51;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;
    UINT value = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_emta_remain_renew_time with valid pValue");
    status = dhcpv4c_get_emta_remain_renew_time(&value);
    UT_LOG_DEBUG("Return status: %d", status);
    UT_LOG_DEBUG("Return value: %u", value);

    UT_ASSERT_EQUAL(STATUS_SUCCESS, status);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for negative scenario of dhcpv4c_get_emta_remain_renew_time function
*
* This test verifies the behavior of dhcpv4c_get_emta_remain_renew_time function when it is called with a NULL pValue parameter.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 052 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :--------------: | ----------- | --------- | --------------- | ----- |
* |  01 |Invoking dhcpv4c_get_emta_remain_renew_time with NULL pointer  | pValue = NULL | STATUS_FAILURE | Should fail |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_emta_remain_renew_time(void)
{
    gTestID = 52;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_emta_remain_renew_time with NULL pValue");
    status = dhcpv4c_get_emta_remain_renew_time(NULL);
    UT_LOG_DEBUG("Return Status=%d", status);
    UT_ASSERT_EQUAL(STATUS_FAILURE, status);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Unit test to verify the functionality of dhcpv4c_get_emta_remain_rebind_time API.
*
* This test case is designed to ensure that the dhcpv4c_get_emta_remain_rebind_time API returns the remaining time for rebinding the EMTA.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 053
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke dhcpv4c_get_emta_remain_rebind_time API with valid output parameter | *pValue = valid memory location | STATUS_SUCCESS | The API should execute successfully, and the output value should be greater than or equal to 0 and less than or equal to UINT_MAX. |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_emta_remain_rebind_time(void)
{
    gTestID = 53;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    UINT value = 0;
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_emta_remain_rebind_time with valid output parameter");
    status = dhcpv4c_get_emta_remain_rebind_time(&value);

    UT_LOG_DEBUG("Return Status: %d", status);
    UT_LOG_DEBUG("Output Value: %u", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This function tests the functionality of the dhcpv4c_get_emta_remain_rebind_time API, when invoked with null output parameter.
*
* The objective of this test is to verify that the dhcpv4c_get_emta_remain_rebind_time API returns a failure status when invoked with a null output parameter.
*
* **Test Group ID:** Basic: 01 @n
* **Test Case ID:** 054 @n
* **Priority:** High @n@n
*
* **Pre-Conditions:** None @n
* **Dependencies:** None @n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console @n
*
* **Test Procedure:** @n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ------ |
* | 01 | Invoking dhcpv4c_get_emta_remain_rebind_time with null output parameter | NULL | STATUS_FAILURE | Should be fail |
*/
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_emta_remain_rebind_time(void)
{
    gTestID = 54;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);\
    INT status = 0;

    UT_LOG_DEBUG("Invoking dhcpv4c_get_emta_remain_rebind_time with null output parameter");
    status = dhcpv4c_get_emta_remain_rebind_time(NULL);
    UT_LOG_DEBUG("Return Status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

static UT_test_suite_t * pSuite = NULL;

/**
* @brief Register the main tests for this module
*
* @return int - 0 on success, otherwise failure
*/
int test_dhcpv4c_api_hal_l1_register(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L1 dhcpv4c_api]", NULL, NULL);
    if (pSuite == NULL)
    {
        return -1;
    }
    // List of test function names and strings
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_lease_time", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_lease_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_lease_time", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_lease_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_remain_lease_time", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_remain_lease_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_remain_lease_time", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_remain_lease_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_remain_renew_time", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_remain_renew_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_remain_renew_time", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_remain_renew_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_remain_rebind_time", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_remain_rebind_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_remain_rebind_time", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_remain_rebind_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_config_attempts", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_config_attempts);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_config_attempts", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_config_attempts);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_ifname", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_ifname);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_ifname", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_ifname);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_fsm_state", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_fsm_state);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_fsm_state", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_fsm_state);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_ip_addr", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_ip_addr);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_ip_addr", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_ip_addr);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_mask", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_mask);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_dhcpv4c_get_ert_mask", test_l1_dhcpv4c_api_negative1_dhcpv4c_dhcpv4c_get_ert_mask);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_gw", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_gw);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_gw", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_gw);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_dns_svrs", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_dns_svrs);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_dns_svrs", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_dns_svrs);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_dhcp_svr", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_dhcp_svr);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_dhcp_svr", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_dhcp_svr);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_lease_time", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_lease_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_lease_time", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_lease_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_remain_lease_time", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_remain_lease_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_remain_lease_time", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_remain_lease_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_remain_renew_time", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_remain_renew_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_remain_renew_time", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_remain_renew_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_ecm_remain_rebind_time", test_l1_dhcpv4c_api_positive1_dhcpv4c_ecm_remain_rebind_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_remain_rebind_time", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_remain_rebind_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_config_attempts", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_config_attempts);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_ecm_config_attempts", test_l1_dhcpv4c_api_negative1_dhcpv4c_ecm_config_attempts);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_ifname", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_ifname);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_ifname", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_ifname);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_fsm_state", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_fsm_state);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_fsm_state", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_fsm_state);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_ip_addr", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_ip_addr);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_ip_addr", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_ip_addr);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_mask", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_mask);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_mask", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_mask);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_gw", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_gw);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_gw", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_gw);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_dns_svrs", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_dns_svrs);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_dns_svrs", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_dns_svrs);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_dhcp_svr", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_dhcp_svr);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_dhcp_svr", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_dhcp_svr);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_emta_remain_lease_time", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_emta_remain_lease_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_emta_remain_lease_time", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_emta_remain_lease_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_emta_remain_renew_time", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_emta_remain_renew_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_emta_remain_renew_time", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_emta_remain_renew_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_positive1_dhcpv4c_get_emta_remain_rebind_time", test_l1_dhcpv4c_api_positive1_dhcpv4c_get_emta_remain_rebind_time);
    UT_add_test( pSuite, "l1_dhcpv4c_api_negative1_dhcpv4c_get_emta_remain_rebind_time", test_l1_dhcpv4c_api_negative1_dhcpv4c_get_emta_remain_rebind_time);
    return 0;
}