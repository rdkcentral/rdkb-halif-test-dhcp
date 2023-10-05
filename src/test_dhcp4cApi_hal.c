/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:*
* Copyright 2016 RDK Management
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
 
/**
* @file test_dhcp4cApi.c
* @page dhcp4cApi Level 1 Tests
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios).
* This is to ensure that the dhcp4cApi APIs meet the requirements across all vendors.
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [halSpec.md](../../../docs/halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include "dhcp4cApi.h"
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS   0
#endif

#ifndef STATUS_FAILURE
#define STATUS_FAILURE   -1
#endif

#ifndef INT32_MAX
#define INT32_MAX 0x7FFFFFFF
#endif

#ifndef INT32_MIN
#define INT32_MIN (-INT32_MAX - 1)
#endif

#ifndef UINT32_MAX
#define UINT32_MAX 0xFFFFFFFFU
#endif

struct in_addr addr;

int isIpAddressInRange(const char* ip_address, const char* start_range, const char* end_range) {
    struct in_addr addr_ip, addr_start, addr_end;

    if (inet_aton(ip_address, &addr_ip) == 0) {
        fprintf(stderr, "Invalid IP address format: %s\n", ip_address);
        return -1; // Invalid IP address format
    }

    if (inet_aton(start_range, &addr_start) == 0 || inet_aton(end_range, &addr_end) == 0) {
        fprintf(stderr, "Invalid range address format\n");
        return -1; // Invalid range address format
    }

    // Convert IP addresses to host byte order for comparison
    uint32_t ip = ntohl(addr_ip.s_addr);
    uint32_t start = ntohl(addr_start.s_addr);
    uint32_t end = ntohl(addr_end.s_addr);

    // Check if the IP address is within the range
    if (ip >= start && ip <= end) {
        return 1; // IP is in range
    } else {
        return 0; // IP is not in range
    }
}

/**
* @brief Test case to verify the functionality of dhcp4c_get_ert_lease_time function
*
* This test case validates the dhcp4c_get_ert_lease_time function by checking if it returns the expected status and value.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 001
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* Table below shows the steps and input variations tried with their description, test data, expected result, and notes.
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :--------------: | ----------- | --------- | --------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ert_lease_time with valid memory location| *pValue = valid pointer | STATUS_SUCCESS | Value's range should retrieved successfully and within the range 60 to 604800 | 
*/
void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_lease_time(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_lease_time...");
    unsigned int value = 0;
    UT_LOG("Invoking dhcp4c_get_ert_lease_time with pValue = valid memory address");
    int status = dhcp4c_get_ert_lease_time(&value);
    UT_LOG("Function returned status: %d",status);
    UT_LOG("Function returned Value: %u", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if (value >= 60 && value <= 604800) {
        UT_LOG("ert_lease_time is %u which is a valid value.", value);
        UT_PASS("dhcp4c_get_ert_lease_time validation success");
    } else {
	UT_LOG("ert_lease_time is %u which is a invalid value.", value);
        UT_FAIL("dhcp4c_get_ert_lease_time validation failed");	
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_lease_time...");
}

/**
 * @brief Test objective: To verify the behavior of the function dhcp4c_get_ert_lease_time when invoked with a NULL pointer.
 *
 * This test case verifies whether the function dhcp4c_get_ert_lease_time returns the expected status when it is invoked with a NULL pointer as the argument.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 002
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
 *
 * **Test Procedure:**
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | ----------- | ----------------------------------- | -------------------- | -------- |
 * | 01 | Invoking function with a NULL pointer | pValue = NULL | STATUS_FAILURE | Should Fail |
 */
void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_lease_time(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_lease_time...");
    unsigned int *pValue = NULL;
    UT_LOG("Invoking dhcp4c_get_ert_lease_time with pValue = NULL");
    int status = dhcp4c_get_ert_lease_time(pValue);
    UT_LOG("Function returned status: %d",status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_lease_time...");
}

/**
* @brief Test case to validate the function dhcp4c_get_ert_remain_lease_time.
*
* This test case is used to validate the function dhcp4c_get_ert_remain_lease_time. 
* The objective of this test is to verify if the function returns the correct remaining lease time.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 003
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke dhcp4c_get_ert_remain_lease_time with valid pValue| STATUS_SUCCESS | Value's range should retrieved successfully and within the range 0 to UINT32_MAX |
*/
void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_remain_lease_time(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_remain_lease_time...");
    unsigned int value = 0;
    UT_LOG("Invoking dhcp4c_get_ert_remain_lease_time with pValue = &value");
    int status = dhcp4c_get_ert_remain_lease_time(&value);
    UT_LOG("Function returned status: %d",status);
    UT_LOG("Function returned Value: %u", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if (value >= 0 && value <= UINT32_MAX) {
        UT_LOG("ert_remain_lease_time is %u which is a valid value.", value);
        UT_PASS("dhcp4c_get_ert_remain_lease_time validation success");
    } else {
	UT_LOG("ert_remain_lease_time is %u which is a invalid value.", value);
        UT_FAIL("dhcp4c_get_ert_remain_lease_time validation failed");	
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_remain_lease_time...");
}

/**
* @brief This test case verifies the behavior of the dhcp4c_get_ert_remain_lease_time function in a negative scenario.
*
* The test case checks the return status when the function is invoked with a NULL parameter.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 004
* **Priority:** High
* 
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* 
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcp4c_get_ert_remain_lease_time with pValue = NULL | pValue = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/
void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_remain_lease_time(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_remain_lease_time...");
    unsigned int *pValue = NULL;
    UT_LOG("Invoking dhcp4c_get_ert_remain_lease_time with pValue = NULL");
    int status = dhcp4c_get_ert_remain_lease_time(pValue);
    UT_LOG("Function returned status: %d",status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_remain_lease_time...");
}

/**
* @brief Test for the functionality of the dhcp4c_get_ert_remain_renew_time API when provided with valid memory address 
*
* This test validates the functionality of the dhcp4c_get_ert_remain_renew_time API by checking if the correct remaining time for Ethernet Renew is obtained.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 005
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data |Expected Result |Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke dhcp4c_get_ert_remain_renew_time with valid pValue| Value = valid memory address | STATUS_SUCCESS | Value's range should retrieved successfully and within the range 0 to UINT32_MAX |
*/
void test_l1_dhcp4cApi_hal_positive1_get_ert_remain_renew_time(void) {
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_get_ert_remain_renew_time...");
    unsigned int value = 0;
    UT_LOG("Invoking dhcp4c_get_ert_remain_renew_time with pValue = valid memory address");
    int status = dhcp4c_get_ert_remain_renew_time(&value);
    UT_LOG("Return status: %d", status);
    UT_LOG("Return value: %u", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if(value >= 0 && value <= UINT32_MAX) {
       UT_LOG("ert_remain_renew_time is %u which is a valid value.", value);
       UT_PASS("dhcp4c_get_ert_remain_renew_time validation success");
    } else {
	UT_LOG("ert_remain_renew_time is %u which is a invalid value.", value);
        UT_FAIL("dhcp4c_get_ert_remain_renew_time validation failed");	
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_get_ert_remain_renew_time...");
}

/**
 * @brief This function tests the dhcp4c_get_ert_remain_renew_time function, specifically for a negative case where the input pointer is NULL.
 * 
 * This test verifies whether the dhcp4c_get_ert_remain_renew_time function correctly handles the case where the input pointer is NULL by returning a STATUS_FAILURE.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 006
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via the console.
 *
 * **Test Procedure:**
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Verify behavior when the input pointer is NULL | pValue = NULL | STATUS_FAILURE | The function should return a STATUS_FAILURE |
 */
void test_l1_dhcp4cApi_hal_negative1_get_ert_remain_renew_time(void) {
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_get_ert_remain_renew_time...");
    unsigned int *pValue = NULL;
    UT_LOG("Invoking dhcp4c_get_ert_remain_renew_time with pValue = NULL");
    int status = dhcp4c_get_ert_remain_renew_time(pValue);
    UT_LOG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_get_ert_remain_renew_time...");
}

/**
* @brief Unit test to verify the functionality of dhcp4c_get_ert_remain_rebind_time function
*
* This test case is used to verify the functionality of the dhcp4c_get_ert_remain_rebind_time 
* function by testing if it retrieves the remaining time for rebind in the Extended
* Response Timer (ERT) option correctly.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 007
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke dhcp4c_get_ert_remain_rebind_time with valid pValue| Value = valid memory address | STATUS_SUCCESS | Value's range should retrieved successfully and within the range 0 to (2^32)-1 |
*/

void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_remain_rebind_time(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_remain_rebind_time...");
    unsigned int value = 0;
    UT_LOG("Invoking dhcp4c_get_ert_remain_rebind_time with valid memory address...");
    int status = dhcp4c_get_ert_remain_rebind_time(&value);
    UT_LOG("Return status: status=%d", status);
    UT_LOG("Output value: value=%u", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if (value >= 0 && value <= UINT32_MAX) {
        UT_LOG("ert_remain_rebind_time is %u which is a valid value.", value);
        UT_PASS("dhcp4c_get_ert_remain_rebind_time validation success");
    } else {
	UT_LOG("ert_remain_rebind_time is %u which is a invalid value.", value);
        UT_FAIL("dhcp4c_get_ert_remain_rebind_time validation failed");	
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_remain_rebind_time...");
}

/**
 * @brief Test case to validate the negative scenario of dhcp4c_get_ert_remain_rebind_time function
 *
 * This test case verifies the behavior of dhcp4c_get_ert_remain_rebind_time function when invoked with a NULL pointer.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 008
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
 *
 * **Test Procedure:**
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :--------------: | ----------- | --------- | --------------- | ----- |
 * |       01         | Invoking dhcp4c_get_ert_remain_rebind_time with NULL pointer | pValue = NULL | Failure status | Should be failure |
 */
void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_remain_rebind_time(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_remain_rebind_time...");
    unsigned int *pValue = NULL;
    UT_LOG("Invoking dhcp4c_get_ert_remain_rebind_time with NULL pointer...");
    int status = dhcp4c_get_ert_remain_rebind_time(pValue);
    UT_LOG("Return status: status=%d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_remain_rebind_time...");
}

/**
    * @brief Test case to verify the functionality of "dhcp4c_get_ert_config_attempts" API.
    *
    * This test case verifies that the "dhcp4c_get_ert_config_attempts" API returns the correct value for the number of attempts to retrieve ERT configuration.
    *
    * **Test Group ID:** Basic: 01
    * **Test Case ID:** 009
    * **Priority:** High
    * 
    * **Pre-Conditions:** None
    * **Dependencies:** None
    * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
    * 
    * **Test Procedure:**
    * | Variation / Step | Description | Test Data | Expected Result | Notes |
    * | :----: | --------- | ---------- | -------------- | ----- |
    * | 01 | Invoking "dhcp4c_get_ert_config_attempts" API with valid memory address for pValue | pValue = valid memory address | status = STATUS_SUCCESS, value >= 0 and value <= UINT_MAX | Should be successful |
    */
void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_config_attempts(void) {
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_config_attempts...");
    int value = 0;
    UT_LOG("Invoking dhcp4c_get_ert_config_attempts with input parameters: pValue = valid memory address");
    int status = dhcp4c_get_ert_config_attempts(&value);
    UT_LOG("Return status = %d", status);
    UT_LOG("Return value = %d", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if(value >= 0 && value <= 2147483647){
       UT_LOG("ert_config_attempts is %d which is a valid value.", value);
       UT_PASS("dhcp4c_get_ert_config_attempts validation success");
    } else {
	UT_LOG("ert_config_attempts is %d which is a invalid value.", value);
        UT_FAIL("dhcp4c_get_ert_config_attempts validation failed");	
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_config_attempts...");
}

/**
* @brief Test case to verify the negative scenario of dhcp4c_get_ert_config_attempts() function.
*
* This test case is used to verify the behavior of dhcp4c_get_ert_config_attempts() function when NULL is passed as input parameter.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 010
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Verify behavior when NULL is passed as input parameter | pValue = NULL | STATUS_FAILURE | Should Fail |
*/
void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_config_attempts(void) {
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_config_attempts...");
    int *pValue = NULL;
    UT_LOG("Invoking dhcp4c_get_ert_config_attempts with input parameters: pValue = NULL");
    int status = dhcp4c_get_ert_config_attempts(pValue);
    UT_LOG("Return  status = %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_config_attempts...");
}

/**
* @brief This test case verifies the functionality of the dhcp4c_get_ert_ifname function to get the ERT interface name.
*
* The objective of this test case is to ensure that the dhcp4c_get_ert_ifname function returns the ERT interface name correctly.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 011
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :--------------: | ----------- | --------- | --------------- | ----- |
* | 01 | Invoke dhcp4c_get_ert_ifname with valid memory address for pValue(64 bytes) | pValue = valid memory address | STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_ifname(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_ifname...");
    char pValue[64] = {"\0"};
    UT_LOG("Invoking dhcp4c_get_ert_ifname with valid memory address.");
    // Test the positive case
    int result = dhcp4c_get_ert_ifname(pValue);
    UT_LOG("Return  status = %d", result);
    UT_LOG("Return value = %s",pValue);
    UT_ASSERT_EQUAL(result, STATUS_SUCCESS);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_ifname...");
}

/**
 * @brief This test case is used to verify the functionality of the dhcp4c_get_ert_ifname function when a NULL pointer is passed as the argument.
 *
 * The purpose of this test is to ensure that the function dhcp4c_get_ert_ifname can handle the case when a NULL pointer is passed as the argument.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 012
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
 *
 * **Test Procedure:**
 * 
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | ----------- | --------- |---------------- | ----- |
 * | 01 | Invoke dhcp4c_get_ert_ifname with pValue as NULL. | pValue = NULL | result = STATUS_FAILURE | Should return STATUS_FAILURE |
 */
void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_ifname(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_ifname...");
    char *pValue = NULL;
    UT_LOG("Invoking dhcp4c_get_ert_ifname with NULL pointer.");
    // Test the negative case
    int result = dhcp4c_get_ert_ifname(pValue);
    UT_LOG("Return  status = %d", result);
    UT_ASSERT_EQUAL(result, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_ifname...");
}

/**
 * @brief This function tests the dhcp4c_get_ert_fsm_state() API to check if it returns the correct ERT FSM state value.
 *
 * The objective of this test is to ensure that the dhcp4c_get_ert_fsm_state() API returns the expected ERT FSM state value and the function returns STATUS_SUCCESS.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 013
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
 *
 * **Test Procedure:**
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking dhcp4c_get_ert_fsm_state() with valid pValue pointer. | STATUS_SUCCESS, pValue is between 0 to 6. | Should be successful |
 */

void test_l1_dhcp4cApi_hal_positive1_GetErtFsmState(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_GetErtFsmState...");
    int value = 0;
    UT_LOG("Invoking dhcp4c_get_ert_fsm_state() with valid pValue pointer.");
    int result = dhcp4c_get_ert_fsm_state(&value);
    UT_LOG("Return  status = %d", result);
    UT_LOG("Return  value = %d", value);
    UT_ASSERT_EQUAL(result, STATUS_SUCCESS);
    if(value >= 1 && value <= 6){
        UT_LOG("ert_fsm_stat is %d which is a valid value.", value);
        UT_PASS("dhcp4c_get_ert_fsm_state validation success");
    } else {
	UT_LOG("ert_fsm_stat is %d which is a invalid value.", value);
        UT_FAIL("dhcp4c_get_ert_fsm_state validation failed");	
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_GetErtFsmState...");
}

/**
* @brief This test case checks the behavior of the dhcp4c_get_ert_fsm_state() function when a NULL pointer is passed as the argument.
*
* The objective of this test is to verify that the function returns STATUS_FAILURE when a NULL pointer is passed as the argument.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 014
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Passing a NULL pointer as the argument | pValue = NULL | STATUS_FAILURE | should be STATUS_FAILURE |
*/
void test_l1_dhcp4cApi_hal_negative1_GetErtFsmState_NullPointer(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_GetErtFsmState_NullPointer...");
    int *pValue = NULL;
    UT_LOG("Invoking dhcp4c_get_ert_fsm_state() with pValue as NULL pointer.");
    int result = dhcp4c_get_ert_fsm_state(pValue);
    UT_LOG("Return  status = %d", result);
    UT_ASSERT_EQUAL(result, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_GetErtFsmState_NullPointer...");
}

/**
 * @brief This test case is used to verify the dhcp4c_get_ert_ip_addr function.
 *
 * The purpose of this test is to verify the correctness of the dhcp4c_get_ert_ip_addr function by checking its return status and output IP address.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 015
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
 *
 * **Test Procedure:**
 *
 * | Variation / Step | Description | Test Data | Expected Result | Notes  |
 * | :--------------: | ------------| ---------------------| -------------------------------- | -------------------- |
 * | 01 | Invoking dhcp4c_get_ert_ip_addr with valid memory address | pValue = valid pointer | STATUS_SUCCESS | Should pass and pValue should be within 1-127 or 128-191 or 192-223 |
 *
 */
void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_ip_addr(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_ip_addr...");
    unsigned int ipAddr = 0;
    char ip_str[20] = "";
    UT_LOG("Invoking dhcp4c_get_ert_ip_addr with valid memory address...");
    int status = dhcp4c_get_ert_ip_addr(&ipAddr);
    UT_LOG("Return Status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    memset(&addr, 0, sizeof(struct in_addr));
    addr.s_addr = ipAddr;
    strcpy(ip_str,inet_ntoa(addr));
    UT_LOG("ip_str: %s", ip_str);
   if (isIpAddressInRange(ip_str,"1.0.0.0","127.0.0.0") || isIpAddressInRange(ip_str,"128.0.0.0","191.255.0.0") || isIpAddressInRange(ip_str,"192.0.0.0","223.255.255.0")){
        UT_LOG("ert_ip_addr is %s which is a valid value.", ip_str);
        UT_PASS("dhcp4c_get_ert_ip_addr validation success");
    } else{
        UT_LOG("ert_ip_addr is %s which is a invalid value.", ip_str);
        UT_FAIL("dhcp4c_get_ert_ip_addr validation failed");
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_ip_addr...");
}

/**
* @brief This test case is used to verify the functionality of the dhcp4c_get_ert_ip_addr API when a NULL pointer is passed as input.
*
* The purpose of this test is to check if the API correctly handles the scenario when a NULL pointer is provided as input. 
* This is important to ensure that the API behaves as expected and does not result in any unexpected behavior or crashes.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 016
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcp4c_get_ert_ip_addr with NULL pointer. | NULL | STATUS_FAILURE | should be STATUS_FAILURE |
*/
void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_ip_addr(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_ip_addr...");
    UT_LOG("Invoking dhcp4c_get_ert_ip_addr with NULL pointer...");
    int status = dhcp4c_get_ert_ip_addr(NULL);
    UT_LOG("Return Status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_ip_addr...");
}

/**
* @brief This test case verifies the functionality of the dhcp4c_get_ert_mask function.
*
* The purpose of this test is to ensure that the dhcp4c_get_ert_mask function returns the expected status and populates the provided value parameter with the correct Ethernet mask.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 017
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcp4c_get_ert_mask with valid memory address | pValue = valid buffer| STATUS_SUCCESS | pValue range for every octet is between 0 to 255 |
*/
void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_mask(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_mask...");
    unsigned int value = 0;
    unsigned int octet1 = 0;
    unsigned int octet2 = 0;
    unsigned int octet3 = 0;
    unsigned int octet4 = 0;

    UT_LOG("Invoking dhcp4c_get_ert_mask with pValue = %u", value);
    int status = dhcp4c_get_ert_mask(&value);
    UT_LOG("Returned status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    octet1 = (value >> 24) & 0xFF;
    octet2 = (value >> 16) & 0xFF;
    octet3 = (value >> 8) & 0xFF;
    octet4 = value & 0xFF;
    if((octet1 >=0 && octet1 <= 255) && (octet2 >=0 && octet2 <= 255) && (octet3 >=0 && octet3 <= 255) && (octet4 >=0 && octet4 <= 255)){
	UT_LOG("octet1 is %x, octet2 is %x, octet3 is %x, octet4 is %x which are  valid values.", octet1,octet2,octet3,octet4 );
        UT_PASS("dhcp4c_get_ert_mask validation success");
    } else{
	UT_LOG("octet1 is %x, octet2 is %x, octet3 is %x, octet4 is %x . there is one invalid value",octet1,octet2,octet3,octet4 );
        UT_FAIL("dhcp4c_get_ert_mask validation failed");		
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_mask...");
}

/**
 * @brief Test to verify correct behavior of dhcp4c_get_ert_mask function in negative scenario.
 *
 * This test checks the behavior of dhcp4c_get_ert_mask function when invoked with a NULL pointer as the input parameter.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 018
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
 *
 * **Test Procedure:**
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :--------------: | ----------- | --------- | --------------- | ----- |
 * |       01         | Invoking dhcp4c_get_ert_mask with NULL pointer | pValue = NULL | STATUS_FAILURE | should be STATUS_FAILURE |
 */
void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_mask(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_mask...");
    unsigned int *pValue = NULL;
    UT_LOG("Invoking dhcp4c_get_ert_mask with pValue = %p", pValue);
    int status = dhcp4c_get_ert_mask(pValue);
    UT_LOG("Returned status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_mask...");
}

/**
* @brief Test the function dhcp4c_get_ert_gw with valid memory address
*
* This test case checks if the function dhcp4c_get_ert_gw returns the expected result
* and if the value of pValue is within the valid ranges.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 019
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcp4c_get_ert_gw with valid memory address | pValue = valid value| STATUS_SUCCESS | Should pass and pValue should be within 1-127 or 128-191 or 192-223 |
*/

void test_l1_dhcp4cApi_hal_positive1_get_ert_gw(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_get_ert_gw...");
    // Preconditions: None
    char ip_str[20] = "";    
    unsigned int ipAddr = 0;
    UT_LOG("Invoking dhcp4c_get_ert_gw with valid memory address");
    int result = dhcp4c_get_ert_gw(&ipAddr);
    // Test case description
    UT_LOG("Return Status: %d", result);
    // Check the return value
    UT_ASSERT_EQUAL(result, STATUS_SUCCESS);
    UT_LOG("ipAddr = %u", ipAddr);
    memset(&addr, 0, sizeof(struct in_addr));
    addr.s_addr = ipAddr;
    strcpy(ip_str,inet_ntoa(addr));
    UT_LOG("ip_str: %s", ip_str);

   if (isIpAddressInRange(ip_str,"1.0.0.0","127.0.0.0") || isIpAddressInRange(ip_str,"128.0.0.0","191.255.0.0") || isIpAddressInRange(ip_str,"192.0.0.0","223.255.255.0")){
        UT_LOG("ert_ip_addr is %s which is a valid value.", ip_str);
        UT_PASS("dhcp4c_get_ert_ip_addr validation success");
    } else {
        UT_LOG("ert_ip_addr is %s which is a invalid value.", ip_str);
        UT_FAIL("dhcp4c_get_ert_ip_addr validation failed");
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_get_ert_gw...");
}

/**
 * @brief Test case to validate the behavior of dhcp4c_get_ert_gw when called with NULL pointer.
 *
 * This test case aims to verify the behavior of dhcp4c_get_ert_gw function when called with a NULL pointer. It checks if the function correctly handles the NULL pointer and returns the expected result.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 020
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
 *
 * **Test Procedure:**
 * | Variation / Step | Description | Test Data | Expected Result | Notes 
 * | 01 | Invoking dhcp4c_get_ert_gw with NULL pointer | pValue = NULL | STATUS_FAILURE | Should FAIL |
 */
void test_l1_dhcp4cApi_hal_negative1_get_ert_gw(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_get_ert_gw...");
    // Preconditions: None
    unsigned int *pValue = NULL;
    UT_LOG("Invoking dhcp4c_get_ert_gw with NULL pointer");
    int result = dhcp4c_get_ert_gw(pValue);
    // Test case description
    UT_LOG("Return Status: %d", result);
    // Check the return value
    UT_ASSERT_EQUAL(result, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_get_ert_gw...");
}

/**
* @brief This test case verifies the functionality of the `dhcp4c_get_ert_dns_svrs` API.
*
* This test case checks if the API `dhcp4c_get_ert_dns_svrs` returns valid IP addresses on success.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 021
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking `dhcp4c_get_ert_dns_svrs` with valid address | pValue = Valid address | STATUS_SUCCESS | Should pass and pValue should be within 1-127 or 128-191 or 192-223 |
*/

void test_l1_dhcp4cApi_hal_positive1_get_ert_dns_svrs(void) {
    UT_LOG("Entering test_l1_dhcp4c_api_positive1_dhcpv4c_get_ert_dns_svrs...");
    char ip_str[20] = "";
    int dns_svrs = 0;
    ipv4AddrList_t ip_list;
    memset(&ip_list, 0, sizeof(ipv4AddrList_t));
    UT_LOG("Invoking dhcp4c_get_ert_dns_svrs with valid memory for ipv4AddrList_t");
    int status = dhcp4c_get_ert_dns_svrs(&ip_list);
    UT_LOG("Return status: %d", status);
    UT_LOG("Number of IP addresses: %d", ip_list.number);
    UT_LOG("First IP address: %u.%u.%u.%u", ip_list.addrList[0], ip_list.addrList[1], ip_list.addrList[2], ip_list.addrList[3]);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if (((ip_list.number >= -2147483648)&&(ip_list.number <= 2147483647)) || ((ip_list.number >= 1)&&(ip_list.number <= 4))) {
        UT_LOG("number of ert_dns_svrs is %d which is a valid value.", ip_list.number);
        UT_PASS("dhcp4c_get_ert_dns_svrs validation success");
    } else {
	UT_LOG("number of ert_dns_svrs is %d which is a invalid value.", ip_list.number);
        UT_FAIL("dhcp4c_get_ert_dns_svrs validation failed");		
    }
   
   for (dns_svrs = 0; dns_svrs < ip_list.number; dns_svrs++) {
        memset(ip_str, 0, sizeof(ip_str));
	memset(&addr, 0, sizeof(addr));
        addr.s_addr = ip_list.addrList[dns_svrs];
        strcpy(ip_str,inet_ntoa(addr));
        UT_LOG("Return value after modification: %s", ip_str);
        /* Verify IP address falls within valid ranges */
        if (isIpAddressInRange(ip_str,"1.0.0.0","127.0.0.0") || isIpAddressInRange(ip_str,"128.0.0.0","191.255.0.0") || isIpAddressInRange(ip_str,"192.0.0.0","223.255.255.0")){
           UT_LOG("ert_dns_svrs is %s which is a valid value.", ip_str);
           UT_PASS("dhcp4c_get_ert_dns_svrs validation success");
        } else {
           UT_LOG("ert_dns_svrs is %s which is a invalid value.", ip_str);
           UT_FAIL("dhcp4c_get_ert_dns_svrs validation failed");
        }
   }
   UT_LOG("Exiting test_l1_dhcp4c_api_positive1_dhcpv4c_get_ecm_dns_svrs...");
}

/**
* @brief Test case to verify negative scenario of dhcp4c_get_ert_dns_svrs function.
*
* This test case verifies the behavior of dhcp4c_get_ert_dns_svrs function when pList is NULL.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 022
* **Priority:** High
* 
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* 
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Verify behavior when pList is NULL | pList = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/
void test_l1_dhcp4cApi_hal_negative1_get_ert_dns_svrs(void) {
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_get_ert_dns_svrs...");
    UT_LOG("Invoking dhcp4c_get_ert_dns_svrs with pList: NULL");
    int result = dhcp4c_get_ert_dns_svrs(NULL);
    UT_LOG("Return Status: %d", result);
    UT_ASSERT_EQUAL(result, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_get_ert_dns_svrs...");
}

/**
 * @brief Test for the function dhcp4c_get_ert_dhcp_svr to verify its positive functionality.
 *
 * This test verifies the positive functionality of the dhcp4c_get_ert_dhcp_svr function. It checks whether the function returns the expected IP address value in the output parameter ipAddr.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 023
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If the user chooses to run the test in interactive mode, this test case has to be selected via console.
 *
 * **Test Procedure:**
 * | Variation / Step | Description                   | Test Data                   | Expected Result    | Notes |
 * | :------------: | ------------------------------- | --------------------------- | ------------------ | ------------------ |
 * |       01       | Invoking dhcp4c_get_ert_dhcp_svr with valid memory address. | ipAddr with valid Address | STATUS_SUCCESS | Should pass and pValue should be within 1-127 or 128-191 or 192-223 |
 *
 */
void test_l1_dhcp4cApi_hal_positive1_get_ert_dhcp_svr(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_get_ert_dhcp_svr...");
    unsigned int ipAddr = 0;
    char ip_str[20] = "";    
    int result = 0;
    UT_LOG("Invoking dhcp4c_get_ert_dhcp_svr with valid memory address.");
    result = dhcp4c_get_ert_dhcp_svr(&ipAddr);
    UT_LOG("Return Status: %d", result);
    UT_LOG("Output: ipAddr = %u", ipAddr);
    UT_ASSERT_EQUAL(result, STATUS_SUCCESS);
    memset(&addr, 0, sizeof(struct in_addr));
    addr.s_addr = ipAddr;
    strcpy(ip_str,inet_ntoa(addr));
    UT_LOG("ip_str: %s", ip_str);

   if (isIpAddressInRange(ip_str,"1.0.0.0","127.0.0.0") || isIpAddressInRange(ip_str,"128.0.0.0","191.255.0.0") || isIpAddressInRange(ip_str,"192.0.0.0","223.255.255.0")) {
        UT_LOG("ert_ip_addr is %s which is a valid value.", ip_str);
        UT_PASS("dhcp4c_get_ert_ip_addr validation success");
    } else {
        UT_LOG("ert_ip_addr is %s which is a invalid value.", ip_str);
        UT_FAIL("dhcp4c_get_ert_ip_addr validation failed");
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_get_ert_dhcp_svr...");
}

/**
 * @brief This test is to validate the negative scenario of the dhcp4c_get_ert_dhcp_svr function where a NULL pointer is passed as an argument.
 *
 * The objective of this test is to ensure that when a NULL pointer is passed to the dhcp4c_get_ert_dhcp_svr function, it returns STATUS_FAILURE as expected.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 024
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
 *
 * **Test Procedure:**
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | ----- | ---------------| ------------------ | ----- |
 * | 01 | Passing a NULL pointer | pointer = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
 */

void test_l1_dhcp4cApi_hal_negative1_get_ert_dhcp_svr(void)
{
    int result;
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_get_ert_dhcp_svr...");
    UT_LOG("Invoking dhcp4c_get_ert_dhcp_svr with NULL pointer.");
    result = dhcp4c_get_ert_dhcp_svr(NULL);
    UT_LOG("Return Status: %d", result);
    UT_LOG("Expected Result: STATUS_FAILURE");
    UT_ASSERT_EQUAL(result, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_get_ert_dhcp_svr...");
}

/**
 * @brief This test case is used to verify the functionality of the dhcp4c_get_ecm_lease_time function.
 *
 * This test case checks whether the dhcp4c_get_ecm_lease_time function can successfully retrieve the ECM lease time value.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 025
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If the user chooses to run the test in interactive mode, they can select this test case via the console.
 *
 * **Test Procedure:**
 * | Variation / Step | Description                                      | Test Data                     | Expected Result                                   | Notes            |
 * | :--------------: | ------------------------------------------------ | ----------------------------- | ------------------------------------------------- | ---------------- |
 * | 01 | Invoking dhcp4c_get_ecm_lease_time with valid memory address | pValue = valid memory address, range is 60 to 604800  | STATUS_SUCCESS | Should be successful |
 */
void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_lease_time(void)
{
    unsigned int value = 0;
    // Log entering test function
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_lease_time...");
    // Invoke the API
    UT_LOG("Invoking dhcp4c_get_ecm_lease_time with valid memory address (pValue=%p)", &value);
    int status = dhcp4c_get_ecm_lease_time(&value);
    // Log the test description and expected output
    UT_LOG("Output: value=%u, status=%d", value, status);
    // Check the return value
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if (value >= 60 && value <= 604800) {
        UT_LOG("ecm_lease_time is %u which is a valid value.", value);
        UT_PASS("dhcp4c_get_ecm_lease_time validation success");
    } else {
	UT_LOG("ecm_lease_time is %u which is a invalid value.", value);
        UT_FAIL("dhcp4c_get_ecm_lease_time validation failed");	
    }
    // Log exiting test function
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_lease_time...");
}

/**
* @brief Test the negative case of the dhcp4c_get_ecm_lease_time function.
*
* This test verifies that the dhcp4c_get_ecm_lease_time function returns STATUS_FAILURE when invoked with a NULL pointer as the parameter.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 026
* **Priority:** High
* 
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* 
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke dhcp4c_get_ecm_lease_time with a NULL pointer | pValue=NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/

void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_lease_time(void)
{
    unsigned int *pValue = NULL;
    // Log entering test function
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_lease_time...");  
    UT_LOG("Invoking dhcp4c_get_ecm_lease_time with NULL pointer (pValue=NULL)");
    // Invoke the API
    int status = dhcp4c_get_ecm_lease_time(pValue);
    // Log the test description and expected output
    UT_LOG("Output: status=%d", status);
    // Check the return value
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    // Log exiting test function
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_lease_time...");
}

/**
* @brief Test case to verify the functionality of dhcp4c_get_ecm_remain_lease_time function
*
* This test case verifies the functionality of dhcp4c_get_ecm_remain_lease_time function by checking if the function returns the expected result and the status is set to STATUS_SUCCESS.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 027
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | ----------- | --------- | --------------- | ----- |
* | 01 | Invoke dhcp4c_get_ecm_remain_lease_time | pValue with valid address | STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_remain_lease_time(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_remain_lease_time...");
    unsigned int value = 0;
    UT_LOG("Invoking dhcp4c_get_ecm_remain_lease_time with pValue = %p", &value);
    int status = dhcp4c_get_ecm_remain_lease_time(&value);
    UT_LOG("Return status: %d", status);
    UT_LOG("Output values: value = %u", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if (value >= 0 && value <= UINT32_MAX) {
        UT_LOG("ecm_remain_lease_tim is %u which is a valid value.", value);
        UT_PASS("dhcp4c_get_ecm_remain_lease_time validation success");
    } else {
	UT_LOG("ecm_remain_lease_tim is %u which is a invalid value.", value);
        UT_FAIL("dhcp4c_get_ecm_remain_lease_time validation failed");	
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_remain_lease_time...");
}

/**
* @brief Test case to verify the functionality of dhcp4c_get_ecm_remain_lease_time for negative scenario.
*
* This test case is to verify the functionality of dhcp4c_get_ecm_remain_lease_time function when invoked with pValue as NULL.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 028
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke dhcp4c_get_ecm_remain_lease_time function with pValue as NULL | pValue = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/

void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_remain_lease_time(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_remain_lease_time...");
    unsigned int *pValue = NULL;
    UT_LOG("Invoking dhcp4c_get_ecm_remain_lease_time with pValue = NULL");
    int status = dhcp4c_get_ecm_remain_lease_time(pValue);
    UT_LOG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_remain_lease_time...");
}

/**
* @brief This test case tests the functionality of dhcp4c_get_ecm_remain_renew_time API.
*
* The objective of this test is to verify that the API dhcp4c_get_ecm_remain_renew_time returns the correct remaining time to renew the ECM interface.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 029
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke dhcp4c_get_ecm_remain_renew_time with valid buffer| pValue = valid address | success | Should be successful |
*/

void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_remain_renew_time(void)
{
    unsigned int value = 0;
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_remain_renew_time...");
    // Preconditions
    // Input
    UT_LOG("Invoking dhcp4c_get_ecm_remain_renew_time with valid memory address...");
    int status = dhcp4c_get_ecm_remain_renew_time(&value);
    UT_LOG("Return status: %d", status);
    UT_LOG("ECM Interface Remaining Time to Renew: %u seconds", value);
    // Asserts
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if (value >= 0 && value <= UINT32_MAX) {
        UT_LOG("ecm_remain_renew_time is %u which is a valid value.", value);
        UT_PASS("dhcp4c_get_ert_lease_time validation success");
    } else {
	UT_LOG("ecm_remain_renew_time is %u which is a invalid value.", value);
        UT_FAIL("dhcp4c_get_ert_lease_time validation failed");	
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_remain_renew_time...");
}

/**
* @brief Test to verify the behavior of the dhcp4c_get_ecm_remain_renew_time function when NULL pointer is passed as input.
*
* This test verifies that the dhcp4c_get_ecm_remain_renew_time function returns STATUS_FAILURE when NULL pointer is passed as input.
* 
* **Test Group ID:** Basic: 01
* **Test Case ID:** 030
* **Priority:** High
* 
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* 
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke dhcp4c_get_ecm_remain_renew_time with NULL | pointer = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/

void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_remain_renew_time(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_remain_renew_time...");
    // Preconditions
    unsigned int *pValue = NULL;
    // Input
    UT_LOG("Invoking dhcp4c_get_ecm_remain_renew_time with NULL pointer...");
    int status = dhcp4c_get_ecm_remain_renew_time(pValue);
    UT_LOG("Return status: %d", status); 
    // Asserts
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_remain_renew_time...");
}

/**
 * @brief Test the function dhcp4c_get_ecm_remain_rebind_time() for positive scenario.
 *
 * The objective of this test is to verify the correctness of the dhcp4c_get_ecm_remain_rebind_time() function
 * when it is called with valid inputs and the value is returned successfully.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 031
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
 *
 * **Test Procedure:**
 * 01. First set of conditions:
 *    | Variation / Step | Description | Test Data | Expected Result | Notes |
 *    | :--------------: | ----------- | --------- | --------------- | ----- |
 *    |       01         | Invoke dhcp4c_get_ecm_remain_rebind_time with valid memory | pValue = &value  | STATUS_SUCCESS  | Should be successful |
 */
void test_l1_dhcp4c_get_ecm_remain_rebind_time_positive1(void) {
    UT_LOG("Entering test_l1_dhcp4c_get_ecm_remain_rebind_time_positive1...");
    unsigned int value = 0;
    UT_LOG("Invoking dhcp4c_get_ecm_remain_rebind_time with pValue = %p", &value);
    int result = dhcp4c_get_ecm_remain_rebind_time(&value);
    UT_LOG("Returned value: %d", result);
    UT_ASSERT_EQUAL(result, STATUS_SUCCESS);
    if (value >= 0 && value <= UINT32_MAX) {
        UT_LOG("ecm_remain_rebind_time is %u which is a valid value.", value);
        UT_PASS("dhcp4c_get_ecm_remain_rebind_time validation success");
    } else { 
	UT_LOG("ecm_remain_rebind_time is %u which is a invalid value.", value);
        UT_FAIL("dhcp4c_get_ecm_remain_rebind_time validation failed");	
    }
    UT_LOG("Exiting test_l1_dhcp4c_get_ecm_remain_rebind_time_positive1...");
}

/**
* @brief Test to verify the functionality of dhcp4c_get_ecm_remain_rebind_time API when a NULL pointer is provided as input.
*
* This test case is performing a negative test where the API is invoked with a NULL pointer as input. 
* The purpose of this test is to verify that the API handles the NULL pointer gracefully and returns a failure status.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 032
* **Priority:** High
* 
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* 
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcp4c_get_ecm_remain_rebind_time with pValue = NULL | pValue = NULL | STATUS_FAILURE | Should return failure status |
*/
void test_l1_dhcp4c_get_ecm_remain_rebind_time_negative1(void) {
    UT_LOG("Entering test_l1_dhcp4c_get_ecm_remain_rebind_time_negative1...");
    unsigned int *pValue = NULL;
    UT_LOG("Invoking dhcp4c_get_ecm_remain_rebind_time with pValue = NULL");
    int result = dhcp4c_get_ecm_remain_rebind_time(pValue);
    UT_LOG("Returned value: %d", result);
    UT_ASSERT_EQUAL(result, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4c_get_ecm_remain_rebind_time_negative1...");
}

/**
* @brief Test case to verify the functionality of dhcp4c_get_ecm_config_attempts function.
*
* This test case is used to verify if the dhcp4c_get_ecm_config_attempts function returns the expected output when invoked with a valid memory address.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 033
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 |  Invoke dhcp4c_get_ecm_config_attempts with valid memory | pValue = valid memory address | STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcp4cApi_hal_positive1_get_ecm_config_attempts(void) {
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_get_ecm_config_attempts...");
    int pValue = 0;
    UT_LOG("Invoking dhcp4c_get_ecm_config_attempts with a valid memory address. Output: %d", pValue);
    int status = dhcp4c_get_ecm_config_attempts(&pValue);
    UT_LOG("Returned status: %d", status);
    UT_ASSERT_EQUAL(STATUS_SUCCESS, status);
    if (pValue >= -2147483648 && pValue <= 2147483647){
        UT_LOG("get_ecm_config_attempts is %d which is a valid value.", pValue);
        UT_PASS("dhcp4c_get_ecm_config_attempts validation success");
    } else {
	UT_LOG("get_ecm_config_attempts is %d which is a invalid value.", pValue);
        UT_FAIL("dhcp4c_get_ecm_config_attempts validation failed");	
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_get_ecm_config_attempts...");
}

/**
* @brief This test verifies the behavior of the dhcp4c_get_ecm_config_attempts function when called with a NULL pointer.
*
* The purpose of this test is to ensure that the function returns STATUS_FAILURE when it is called with a NULL pointer as input.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 034
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
*
* **Test Procedure:**
* 
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcp4c_get_ecm_config_attempts with a NULL pointer | config_attempts = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/
void test_l1_dhcp4cApi_hal_negative1_get_ecm_config_attempts(void) {
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_get_ecm_config_attempts...");
    int *pValue = NULL;
    UT_LOG("Invoking dhcp4c_get_ecm_config_attempts with a NULL pointer.");
    int status = dhcp4c_get_ecm_config_attempts(pValue);
    UT_LOG("Returned status: %d", status);
    UT_ASSERT_EQUAL(STATUS_FAILURE, status);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_get_ecm_config_attempts...");
}

/**
* @brief Test case to validate the functionality of dhcp4c_get_ecm_ifname API.
*
* This test case is used to verify the functionality of dhcp4c_get_ecm_ifname API.
* The objective of this test is to check if the API is able to successfully retrieve the ECM interface name.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 035
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | ---------  | ---------- | --------------- | ----- |
* | 01 | Invoke dhcp4c_get_ecm_ifname with valid buffer| pName = valid buffer(64 bytes) | STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_ifname(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_ifname...");
    char pName[64] = {"\0"};
    int result;
    UT_LOG("Invoking dhcp4c_get_ecm_ifname with valid pName buffer.");
    result = dhcp4c_get_ecm_ifname(pName);
    UT_LOG("Return Status: %d", result);
    UT_LOG("Output: pName = %s", pName);
    UT_ASSERT_EQUAL(result, STATUS_SUCCESS);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_ifname...");
}

/**
 * @brief Test case to verify the behavior of dhcp4c_get_ecm_ifname function when invoked with a NULL buffer.
 *
 * This test case checks whether the dhcp4c_get_ecm_ifname function returns the expected result when invoked with a NULL buffer as an argument.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 036
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
 *
 * **Test Procedure:**
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Verify the return status when invoked with a NULL buffer | pName = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
 */

void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_ifname(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_ifname...");
    char *pName = NULL;
    int result;
    UT_LOG("Invoking dhcp4c_get_ecm_ifname with NULL pName buffer.");
    result = dhcp4c_get_ecm_ifname(pName);
    UT_LOG("Return Status: %d", result);
    UT_LOG("Output: pName = NULL");
    UT_ASSERT_EQUAL(result, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_ifname...");
}

/**
 * @brief This test is aimed to validate the functionality of dhcp4c_get_ecm_fsm_state API.
 *
 *  The purpose of this test is to ensure that the dhcp4c_get_ecm_fsm_state API returns the correct FSM state and status.
 *
 *  **Test Group ID:** Basic: 01
 *  **Test Case ID:** 037
 *  **Priority:** High
 *
 * **Pre-Conditions:** None.
 * **Dependencies:** None.
 * **User Interaction:** If the user chooses to run the test in interactive mode, the test case has to be selected via console.
 *
 * **Test Procedure:**
 *  | Variation / Step | Description | Test Data | Expected Result | Notes |
 *  | :----: | --------- | ---------- | --------------- | ------- |
 *  | 01 | Invoking dhcp4c_get_ecm_fsm_state() with valid pValue pointer. | pValue = valid buffer | STATUS_SUCCESS | Should be successful | Should pass and return pValue between 0 to 6 range
 */

void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_fsm_state(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_fsm_state...");
    int pValue = 0;
    UT_LOG("Invoking dhcp4c_get_ecm_fsm_state with valid pValue...");
    int result = dhcp4c_get_ecm_fsm_state(&pValue);
    UT_LOG("Returned status: %d pValue: %d", result, pValue);
    UT_ASSERT_EQUAL(STATUS_SUCCESS, result);
    if ((pValue >= 0) && (pValue <= 6)) {
        UT_LOG("ecm_fsm_state is %d which is a valid value.", pValue);
        UT_PASS("dhcp4c_get_ecm_fsm_state validation success");
    } else {
	UT_LOG("ecm_fsm_state is %d which is a invalid value.", pValue);
        UT_FAIL("dhcp4c_get_ecm_fsm_state validation failed");	
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_fsm_state...");
}

/**
* @brief This test case is used to verify the functionality of the dhcp4c_get_ecm_fsm_state function when invoked with a NULL pValue parameter.
*
* The purpose of this test is to ensure that the dhcp4c_get_ecm_fsm_state function properly handles the case when a NULL pValue parameter is provided.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 038
* **Priority:** High
* @n
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
* @n
* **Test Procedure:**@n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcp4c_get_ecm_fsm_state with NULL pValue | pValue = NULL | The function should return STATUS_FAILURE | Should Fail |
*/

void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_fsm_state(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_fsm_state...");
    int *pValue = NULL;
    // Input
    UT_LOG("Invoking dhcp4c_get_ecm_fsm_state with NULL pValue...");
    int result = dhcp4c_get_ecm_fsm_state(pValue);
    // Expected Output
    UT_LOG("Returned status: %d", result);
    UT_ASSERT_EQUAL(STATUS_FAILURE, result);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_fsm_state...");
}

/**
* @brief Test case to validate the dhcp4c_get_ecm_ip_addr API.
*
* This test case is used to verify the functionality of the dhcp4c_get_ecm_ip_addr API. It checks if the API returns the correct IP address of the ECM (Ethernet Channel Manager) device.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 039
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking dhcp4c_get_ecm_ip_addr with valid memory address | pValue = valid address | STATUS_SUCCESS | Should pass and pValue should be within 1-127 or 128-191 or 192-223 |
*/
void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_ip_addr(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_ip_addr...");
    unsigned int ipAddr = 0;
    char ip_str[20] = "";
    // Invoke the API with a valid memory address
    UT_LOG("Invoking dhcp4c_get_ecm_ip_addr with valid memory address...");
    int status = dhcp4c_get_ecm_ip_addr(&ipAddr);
    // Check the return status and log the result
    UT_LOG("Status: %d ipAddr:%u", status, ipAddr);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    memset(&addr, 0, sizeof(struct in_addr));
    addr.s_addr = ipAddr;
    strcpy(ip_str,inet_ntoa(addr));
    UT_LOG("ip_str: %s", ip_str);
    if (isIpAddressInRange(ip_str,"1.0.0.0","127.0.0.0") || isIpAddressInRange(ip_str,"128.0.0.0","191.255.0.0") || isIpAddressInRange(ip_str,"192.0.0.0","223.255.255.0"))     {
        UT_LOG("ert_ip_addr is %s which is a valid value.", ip_str);
        UT_PASS("dhcp4c_get_ert_ip_addr validation success");
    } else {
        UT_LOG("ert_ip_addr is %s which is a invalid value.", ip_str);
        UT_FAIL("dhcp4c_get_ert_ip_addr validation failed");
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_ip_addr...");
}

/**
* @brief Test to verify the behavior of dhcp4c_get_ecm_ip_addr API when invoked with a NULL pointer.
*
* This test is to ensure that the dhcp4c_get_ecm_ip_addr API returns a failure status when invoked with a NULL pointer as input.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 040
* **Priority:** High
* 
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
* 
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcp4c_get_ecm_ip_addr with NULL pointer | pointer = NULL | STATUS_FAILURE | Should return failure status |
*/
void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_ip_addr(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_ip_addr...");
    int status;
    // Invoke the API with a NULL pointer
    UT_LOG("Invoking dhcp4c_get_ecm_ip_addr with NULL pointer...");
    status = dhcp4c_get_ecm_ip_addr(NULL);
    // Check the return status and log the result
    UT_LOG("Return Status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_ip_addr...");
}

/**
 * @brief Test case to verify the functionality of dhcp4c_get_ecm_mask function
 *
 * This test case verifies that the dhcp4c_get_ecm_mask function returns the correct status and populates the value variable correctly.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 041
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
 *
 * **Test Procedure:**
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * |  01    | Invoking dhcp4c_get_ecm_mask with valid memory address| pValue = valid memory | STATUS_SUCCESS | Should be successful |
 */
void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_mask(void) {
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_mask...");
    unsigned int value = 0;
    unsigned int octet1 = 0;
    unsigned int octet2 = 0;
    unsigned int octet3 = 0;
    unsigned int octet4 = 0;
    UT_LOG("Invoking dhcp4c_get_ecm_mask with pValue = %p", &value);
    int status = dhcp4c_get_ecm_mask(&value);
    UT_LOG("Return status: %d", status);
    UT_LOG("Output values: pValue = %u", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    octet1 = (value >> 24) & 0xFF;
    octet2 = (value >> 16) & 0xFF;
    octet3 = (value >> 8) & 0xFF;
    octet4 = value & 0xFF;
    if ((octet1 >=0 && octet1 <= 255) && (octet2 >=0 && octet2 <= 255) && (octet3 >=0 && octet3 <= 255) && (octet4 >=0 && octet4 <= 255)) {
        UT_LOG("octet1 is %x, octet2 is %x, octet3 is %x, octet4 is %x which are  valid values.", octet1,octet2,octet3,octet4 );
        UT_PASS("dhcp4c_get_ert_mask validation success");
    } else {
        UT_LOG("octet1 is %x, octet2 is %x, octet3 is %x, octet4 is %x . there is one invalid value",octet1,octet2,octet3,octet4 );
        UT_FAIL("dhcp4c_get_ert_mask validation failed");
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_mask...");
}

/**
* @brief Test case to verify the functionality of the dhcp4c_get_ecm_mask API with negative input
*
* This test case checks the behavior of the dhcp4c_get_ecm_mask API when the input pointer is NULL.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 042
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | -----             |
* | 01     | Invoking dhcp4c_get_ecm_mask with NULL pointer | pointer = NULL | STATUS_FAILURE | Should Fail |
*/

void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_mask(void) {
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_mask...");
    unsigned int *pValue = NULL;
    UT_LOG("Invoking dhcp4c_get_ecm_mask with pValue = %p", pValue);
    int status = dhcp4c_get_ecm_mask(pValue);
    UT_LOG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_mask...");
}

/**
 * @brief Unit test to validate dhcp4c_get_ecm_gw function.
 *
 * This test case verifies the functionality of dhcp4c_get_ecm_gw function by checking its return status and output value.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 043
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
 *
 * **Test Procedure:**
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :--------------: | ----------- | --------- | --------------- | ----- |
 * || 01 | Invoke dhcp4c_get_ecm_gw with valid memory address | *pValue = valid memory address | STATUS_SUCCESS | Should pass and pValue should be within 1-127 or 128-191 or 192-223 | 
 */
void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_gw(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_gw...");
    unsigned int ipAddr = 0;
    char ip_str[20] = "";
    UT_LOG("Invoking dhcp4c_get_ecm_gw with pValue as valid memory address");
    int status = dhcp4c_get_ecm_gw(&ipAddr);
    UT_LOG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    memset(&addr, 0, sizeof(struct in_addr));
    addr.s_addr = ipAddr;
    strcpy(ip_str,inet_ntoa(addr));
    UT_LOG("ip_str: %s", ip_str);
    if (isIpAddressInRange(ip_str,"1.0.0.0","127.0.0.0") || isIpAddressInRange(ip_str,"128.0.0.0","191.255.0.0") || isIpAddressInRange(ip_str,"192.0.0.0","223.255.255.0")){
        UT_LOG("ert_ip_addr is %s which is a valid value.", ip_str);
        UT_PASS("dhcp4c_get_ert_ip_addr validation success");
    } else{
        UT_LOG("ert_ip_addr is %s which is a invalid value.", ip_str);
        UT_FAIL("dhcp4c_get_ert_ip_addr validation failed");
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_gw...");
}

/**
* @brief Test case to verify the negative scenario of the dhcp4c_get_ecm_gw function.
*
* This test case is designed to test the dhcp4c_get_ecm_gw function when the pValue parameter is passed as NULL.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 044
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoke dhcp4c_get_ecm_gw with pValue as NULL | pValue = NULL | STATUS_FAILURE | Should Fail |
*/
void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_gw(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_gw...");
    UT_LOG("Invoking dhcp4c_get_ecm_gw with pValue as NULL");
    int status = dhcp4c_get_ecm_gw(NULL);
    UT_LOG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_gw...");
}

/**
 * @brief Test case to validate the dhcp4c_get_ecm_dns_svrs API
 *
 * This test case verifies the functionality of dhcp4c_get_ecm_dns_svrs API by checking its response when invoked with a valid pointer but an empty list.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 045
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
 *
 * **Test Procedure:**
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- |-------------- | ----- |
 * | 01 | Invoking dhcpv4c_get_ecm_dns_svrs with a valid memory location | pList = valid pointer to structure ipv4AddrList_t | STATUS_SUCCESS | Should pass and The number of IP addresses should be between 1-4 and pValue should be within 1-127 or 128-191 or 192-223 
 */

void test_l1_dhcp4cApi_hal_positive2_dhcp4c_get_ecm_dns_svrs(void) {
    UT_LOG("Entering test_l1_dhcp4c_api_positive1_dhcpv4c_get_ecm_dns_svrs...");
    char ip_str[20];
    int dns_svrs = 0;
    ipv4AddrList_t ip_list;
    memset(&ip_list, 0, sizeof(ipv4AddrList_t));
    UT_LOG("Invoking dhcp4c_get_ecm_dns_svrs with valid memory for ipv4AddrList_t");
    int status = dhcp4c_get_ecm_dns_svrs(&ip_list);
    UT_LOG("status:%d Number of IP addresses: %d", status, ip_list.number);
    UT_LOG("First IP address: %u.%u.%u.%u", ip_list.addrList[0], ip_list.addrList[1], ip_list.addrList[2], ip_list.addrList[3]);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if (((ip_list.number >= -2147483648)&&(ip_list.number <= 2147483647)) || ((ip_list.number >= 1)&&(ip_list.number <= 4)))
    {
        UT_LOG("number of ert_dns_svrs is %d which is a valid value.", ip_list.number);
        UT_PASS("dhcp4c_get_ecm_dns_svrs validation success");
    } else {
	UT_LOG("number of ert_dns_svrs is %d which is a invalid value.", ip_list.number);
        UT_FAIL("dhcp4c_get_ecm_dns_svrs validation failed");		
   }
   for (dns_svrs = 0; dns_svrs < ip_list.number; dns_svrs++) {
        memset(ip_str, 0, sizeof(ip_str));
	memset(&addr, 0, sizeof(addr));
        addr.s_addr = ip_list.addrList[dns_svrs];
        strcpy(ip_str,inet_ntoa(addr));
	
        UT_LOG("Return value after modification: %s", ip_str);
        /* Verify IP address falls within valid ranges */
        if (isIpAddressInRange(ip_str,"1.0.0.0","127.0.0.0") || isIpAddressInRange(ip_str,"128.0.0.0","191.255.0.0") || isIpAddressInRange(ip_str,"192.0.0.0","223.255.255.0"))     {
           UT_LOG("ert_dns_svrs is %s which is a valid value.", ip_str);
           UT_PASS("dhcp4c_get_ecm_dns_svrs validation success");
        } else {
           UT_LOG("ert_dns_svrs is %s which is a invalid value.", ip_str);
           UT_FAIL("dhcp4c_get_ecm_dns_svrs validation failed");
        }
   }
   UT_LOG("Exiting test_l1_dhcp4c_api_positive1_dhcpv4c_get_ecm_dns_svrs...");
}


/**
* @brief Test case to verify the functionality of dhcp4c_get_ecm_dns_svrs when NULL pointer is passed as argument.
*
* This test case verifies whether the dhcp4c_get_ecm_dns_svrs function returns STATUS_FAILURE when a NULL pointer is passed as an argument.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 046
* **Priority:** High
* 
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via the console.
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Passing NULL pointer | ecm_dns_ptr = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/

void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_dns_svrs(void) {
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_dns_svrs...");
    UT_LOG("Invoking dhcp4c_get_ecm_dns_svrs with NULL pointer");
    int status = dhcp4c_get_ecm_dns_svrs(NULL);
    UT_LOG("Return status: %d", status);
    UT_ASSERT_EQUAL(STATUS_FAILURE,status );
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_dns_svrs...");
}

/**
 * @brief Unit test for dhcp4c_get_ecm_dhcp_svr() function
 *
 * This test case verifies the functionality of the dhcp4c_get_ecm_dhcp_svr() function.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 047
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
 *
 * **Test Procedure:**
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :----: | --------- | ---------- | --------------- | ----- |
 * | 01 | Verify the function with valid input | pValue = valid memory location | STATUS_SUCCESS | Should pass and pValue should be within 1-127 or 128-191 or 192-223 |
 */
void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_dhcp_svr(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_dhcp_svr...");
    unsigned int ipAddr = 0;
    char ip_str[20] = "";
    UT_LOG("Invoking dhcp4c_get_ecm_dhcp_svr() with input parameters (pValue is a valid memory location)...");
    int status = dhcp4c_get_ecm_dhcp_svr(&ipAddr);
    UT_LOG("Return status: status = %d", status);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    memset(&addr, 0, sizeof(struct in_addr));
    addr.s_addr = ipAddr;
    strcpy(ip_str,inet_ntoa(addr));
    UT_LOG("ip_str: %s", ip_str);
   if (isIpAddressInRange(ip_str,"1.0.0.0","127.0.0.0") || isIpAddressInRange(ip_str,"128.0.0.0","191.255.0.0") || isIpAddressInRange(ip_str,"192.0.0.0","223.255.255.0")) {
        UT_LOG("ert_ip_addr is %s which is a valid value.", ip_str);
        UT_PASS("dhcp4c_get_ert_ip_addr validation success");
   } else {
        UT_LOG("ert_ip_addr is %s which is a invalid value.", ip_str);
        UT_FAIL("dhcp4c_get_ert_ip_addr validation failed");
   }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_dhcp_svr...");
}

/**
* @brief Test case to validate the negative scenario when invoking dhcp4c_get_ecm_dhcp_svr() with pValue as NULL.
*
* This test case aims to verify the behavior of the dhcp4c_get_ecm_dhcp_svr() API when called with NULL as the pValue parameter. The expected result is that the status returned by the API should be STATUS_FAILURE.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 048
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If the user chooses to run the test in interactive mode, then the test case has to be selected via console.
*
* **Test Procedure:**
* - | Variation / Step | Description | Test Data | Expected Result | Notes |
* - | :----: | --------- | ---------- |-------------- | ----- |
* - | 01 | Invoking dhcp4c_get_ecm_dhcp_svr() with NULL as pValue | pValue = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/

void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_dhcp_svr(void)
{
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_dhcp_svr...");
    unsigned int *pValue = NULL;
    UT_LOG("Invoking dhcp4c_get_ecm_dhcp_svr() with input parameters (pValue is NULL)...");
    int status = dhcp4c_get_ecm_dhcp_svr(pValue);
    UT_LOG("Return status: status = %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_dhcp_svr...");
}

/**
 * @brief Test the dhcp4c_get_emta_remain_lease_time API function.
 *
 * This test case verifies the functionality of the dhcp4c_get_emta_remain_lease_time API function. It checks whether the API returns the correct remaining lease time for the eMTA device.
 *
 * **Test Group ID:** Basic: 01
 * **Test Case ID:** 049
 * **Priority:** High
 *
 * **Pre-Conditions:** None
 * **Dependencies:** None
 * **User Interaction:** If the user chooses to run the test in interactive mode, they must select the test case via the console.
 *
 * **Test Procedure:**
 * | Variation / Step | Description                                            | Test Data            | Expected Result  | Notes               |
 * | ---------------- | ------------------------------------------------------ | --------------------------------------- | -------------------------| 
 * | 01 | Invoke dhcp4c_get_emta_remain_lease_time with valid buffer | pValue = valid memory location | STATUS_SUCCESS | Should be successful |
 */

void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_emta_remain_lease_time(void)
{
    unsigned int value = 0;
    int result;
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_emta_remain_lease_time...");
    UT_LOG("Invoking dhcp4c_get_emta_remain_lease_time with a valid memory address.");
    result = dhcp4c_get_emta_remain_lease_time(&value);
    UT_LOG("Return status: %d", result);
    UT_LOG("Output value: %u", value);
    UT_ASSERT_EQUAL(result, STATUS_SUCCESS);
    if(value >= 0 && value <= UINT32_MAX){
        UT_LOG("emta_remain_lease_time is %u which is a valid value.", value);
        UT_PASS("dhcp4c_get_emta_remain_lease_time validation success");
    } else{
	UT_LOG("emta_remain_lease_time is %u which is a invalid value.", value);
        UT_FAIL("dhcp4c_get_emta_remain_lease_time validation failed");	
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_emta_remain_lease_time...");
}

/**
* @brief This test is used to verify the behavior of the function dhcp4c_get_emta_remain_lease_time when called with a NULL pointer.
*
* The purpose of this test is to ensure that the function dhcp4c_get_emta_remain_lease_time returns the expected result and does not crash when called with a NULL pointer as input parameter.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 050
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcp4c_get_emta_remain_lease_time with a NULL pointer | pValue = NULL | STATUS_FAILURE | The function should return STATUS_FAILURE |
*/

void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_emta_remain_lease_time(void)
{
    unsigned int *pValue = NULL;
    int result;
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_emta_remain_lease_time...");
    UT_LOG("Invoking dhcp4c_get_emta_remain_lease_time with a NULL pointer.");
    result = dhcp4c_get_emta_remain_lease_time(pValue);
    UT_LOG("Return status: %d", result);
    UT_ASSERT_EQUAL(result, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_emta_remain_lease_time...");
}

/**
* @brief This test case is used to verify the functionality of the dhcp4c_get_emta_remain_renew_time API.
*
* The purpose of this test is to check if the API dhcp4c_get_emta_remain_renew_time returns the correct value for the remaining renewal time of the EMTA lease.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 051
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console.
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcp4c_get_emta_remain_renew_time with valid memory location | pValue = valid buffer | STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcp4cApi_hal_positive1_get_emta_remain_renew_time(void) {
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_get_emta_remain_renew_time...");
    unsigned int value = 0;
    UT_LOG("Invoking dhcp4c_get_emta_remain_renew_time with pValue (%p)", &value);
    int status = dhcp4c_get_emta_remain_renew_time(&value);
    UT_LOG("Return status: %d", status);
    UT_LOG("Received value: %u", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if (value >= 0 && value <= UINT32_MAX){
        UT_LOG("emta_remain_renew_time is %d which is a valid value.", value);
        UT_PASS("dhcp4c_get_emta_remain_renew_time validation success");
    } else{
	UT_LOG("emta_remain_renew_time is %d which is a invalid value.", value);
        UT_FAIL("dhcp4c_get_emta_remain_renew_time validation failed");	
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_get_emta_remain_renew_time...");
}

/**
* @brief Test case to verify the negative scenario of the dhcp4c_get_emta_remain_renew_time function.
*
* This test case is used to verify the failure scenario of the dhcp4c_get_emta_remain_renew_time function. It checks whether the function returns STATUS_FAILURE when the input pointer is NULL.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 052
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
*| Variation / Step | Description   | Test Data | Expected Result | Notes |
*| :--------------: | --------------|-----------|-----------------|-------|
*| 01 | Pass NULL buffer to dhcp4c_get_emta_remain_renew_time API  | pValue = NULL | STATUS_FAILURE | Should Fail |
*/
void test_l1_dhcp4cApi_hal_negative1_get_emta_remain_renew_time(void) {
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_get_emta_remain_renew_time...");
    unsigned int *pValue = NULL;
    UT_LOG("Invoking dhcp4c_get_emta_remain_renew_time with pValue (%p)", pValue);
    int status = dhcp4c_get_emta_remain_renew_time(pValue);
    UT_LOG("Return status: %d", status);    
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_get_emta_remain_renew_time...");
}

/**
* @brief This test case is used to verify the functionality of the
* dhcp4c_get_emta_remain_rebind_time API.
*
* The objective of this test is to ensure that the dhcp4c_get_emta_remain_rebind_time API
* can successfully retrieve the remaining rebind time of the EMTA.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 053
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the
* test case has to be selected via console.
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcp4c_get_emta_remain_rebind_time with valid address | value = valid buffer | STATUS_SUCCESS | Should be successful |
*/
void test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_emta_remain_rebind_time(void) {
    UT_LOG("Entering test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_emta_remain_rebind_time...");
    unsigned int value;
    UT_LOG("Invoking dhcp4c_get_emta_remain_rebind_time with valid value pointer.");
    int result = dhcp4c_get_emta_remain_rebind_time(&value);
    UT_LOG("Returned status: %d", result);
    UT_LOG("Expected Result: STATUS_SUCCESS");
    UT_LOG("Output Value: %u", value);
    UT_ASSERT_EQUAL(result, STATUS_SUCCESS);
    if(value >= 0 && value <= UINT32_MAX){
        UT_LOG("emta_remain_rebind_time is %u which is a valid value.", value);
        UT_PASS("dhcp4c_get_emta_remain_rebind_time validation success");
    } else{
	UT_LOG("emta_remain_rebind_time is %u which is a invalid value.", value);
        UT_FAIL("dhcp4c_get_emta_remain_rebind_time validation failed");	
    }
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_emta_remain_rebind_time...");
}

/**
* @brief Test case to verify the negative scenario of the dhcp4c_get_emta_remain_rebind_time API.
*
* This test case verifies if the dhcp4c_get_emta_remain_rebind_time API returns STATUS_FAILURE when a NULL value pointer is passed as an argument.
*
* **Test Group ID:** Basic: 01
* **Test Case ID:** 054
* **Priority:** High
*
* **Pre-Conditions:** None
* **Dependencies:** None
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console
*
* **Test Procedure:**
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- |-------------- | ----- |
* | 01 | Invoking dhcp4c_get_emta_remain_rebind_time with NULL value pointer | value = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
*/
void test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_emta_remain_rebind_time(void) {
    UT_LOG("Entering test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_emta_remain_rebind_time...");
    unsigned int *pValue = NULL;
    UT_LOG("Invoking dhcp4c_get_emta_remain_rebind_time with NULL value pointer.");
    int result = dhcp4c_get_emta_remain_rebind_time(pValue);
    UT_LOG("Returned Value: %d", result);
    UT_LOG("Expected Result: STATUS_FAILURE");
    UT_ASSERT_EQUAL(result, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_emta_remain_rebind_time...");
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int register_hal_tests(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L1 dhcp4cApi]", NULL, NULL);
    if (pSuite == NULL) {
        return -1;
    }
    // List of test function names and strings
   const char* list1[] = {"l1_dhcp4cApi_positive1_dhcp4c_get_ert_lease_time", "l1_dhcp4cApi_negative1_dhcp4c_get_ert_lease_time", "l1_dhcp4cApi_positive1_dhcp4c_get_ert_remain_lease_time", "l1_dhcp4cApi_negative1_dhcp4c_get_ert_remain_lease_time", "l1_dhcp4cApi_positive1_get_ert_remain_renew_time", "l1_dhcp4cApi_negative1_get_ert_remain_renew_time", "l1_dhcp4cApi_positive1_dhcp4c_get_ert_remain_rebind_time", "l1_dhcp4cApi_negative1_dhcp4c_get_ert_remain_rebind_time", "l1_dhcp4cApi_positive1_dhcp4c_get_ert_config_attempts", "l1_dhcp4cApi_negative1_dhcp4c_get_ert_config_attempts", "l1_dhcp4cApi_positive1_dhcp4c_get_ert_ifname", "l1_dhcp4cApi_negative1_dhcp4c_get_ert_ifname", "l1_dhcp4cApi_positive1_GetErtFsmState", "l1_dhcp4cApi_negative1_GetErtFsmState_NullPointer", "l1_dhcp4cApi_positive1_dhcp4c_get_ert_ip_addr", "l1_dhcp4cApi_negative1_dhcp4c_get_ert_ip_addr", "l1_dhcp4cApi_positive1_dhcp4c_get_ert_mask", "l1_dhcp4cApi_negative1_dhcp4c_get_ert_mask", "l1_dhcp4cApi_positive1_get_ert_gw", "l1_dhcp4cApi_negative1_get_ert_gw", "l1_dhcp4cApi_positive1_get_ert_dns_svrs", "l1_dhcp4cApi_negative1_get_ert_dns_svrs", "l1_dhcp4cApi_positive1_get_ert_dhcp_svr", "l1_dhcp4cApi_negative1_get_ert_dhcp_svr", "l1_dhcp4cApi_positive1_dhcp4c_get_ecm_lease_time", "l1_dhcp4cApi_negative1_dhcp4c_get_ecm_lease_time", "l1_dhcp4cApi_positive1_dhcp4c_get_ecm_remain_lease_time", "l1_dhcp4cApi_negative1_dhcp4c_get_ecm_remain_lease_time", "l1_dhcp4cApi_positive1_dhcp4c_get_ecm_remain_renew_time", "l1_dhcp4cApi_negative1_dhcp4c_get_ecm_remain_renew_time", "l1_dhcp4c_get_ecm_remain_rebind_time_positive1", "l1_dhcp4c_get_ecm_remain_rebind_time_negative1", "l1_dhcp4cApi_positive1_get_ecm_config_attempts", "l1_dhcp4cApi_negative1_get_ecm_config_attempts", "l1_dhcp4cApi_positive1_dhcp4c_get_ecm_ifname", "l1_dhcp4cApi_negative1_dhcp4c_get_ecm_ifname", "l1_dhcp4cApi_positive1_dhcp4c_get_ecm_fsm_state", "l1_dhcp4cApi_negative1_dhcp4c_get_ecm_fsm_state", "l1_dhcp4cApi_positive1_dhcp4c_get_ecm_ip_addr", "l1_dhcp4cApi_negative1_dhcp4c_get_ecm_ip_addr", "l1_dhcp4cApi_positive1_dhcp4c_get_ecm_mask", "l1_dhcp4cApi_negative1_dhcp4c_get_ecm_mask", "l1_dhcp4cApi_positive1_dhcp4c_get_ecm_gw", "l1_dhcp4cApi_negative1_dhcp4c_get_ecm_gw", "l1_dhcp4cApi_positive2_dhcp4c_get_ecm_dns_svrs", "l1_dhcp4cApi_negative1_dhcp4c_get_ecm_dns_svrs", "l1_dhcp4cApi_positive1_dhcp4c_get_ecm_dhcp_svr", "l1_dhcp4cApi_negative1_dhcp4c_get_ecm_dhcp_svr", "l1_dhcp4cApi_positive1_dhcp4c_get_emta_remain_lease_time", "l1_dhcp4cApi_negative1_dhcp4c_get_emta_remain_lease_time", "l1_dhcp4cApi_positive1_get_emta_remain_renew_time", "l1_dhcp4cApi_negative1_get_emta_remain_renew_time", "l1_dhcp4cApi_positive1_dhcp4c_get_emta_remain_rebind_time", "l1_dhcp4cApi_negative1_dhcp4c_get_emta_remain_rebind_time" };
   void (*list2[])() = {test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_lease_time, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_lease_time, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_remain_lease_time, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_remain_lease_time, test_l1_dhcp4cApi_hal_positive1_get_ert_remain_renew_time, test_l1_dhcp4cApi_hal_negative1_get_ert_remain_renew_time, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_remain_rebind_time, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_remain_rebind_time, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_config_attempts, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_config_attempts, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_ifname, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_ifname, test_l1_dhcp4cApi_hal_positive1_GetErtFsmState, test_l1_dhcp4cApi_hal_negative1_GetErtFsmState_NullPointer, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_ip_addr, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_ip_addr, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ert_mask, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ert_mask, test_l1_dhcp4cApi_hal_positive1_get_ert_gw, test_l1_dhcp4cApi_hal_negative1_get_ert_gw, test_l1_dhcp4cApi_hal_positive1_get_ert_dns_svrs, test_l1_dhcp4cApi_hal_negative1_get_ert_dns_svrs, test_l1_dhcp4cApi_hal_positive1_get_ert_dhcp_svr, test_l1_dhcp4cApi_hal_negative1_get_ert_dhcp_svr, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_lease_time, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_lease_time, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_remain_lease_time, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_remain_lease_time, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_remain_renew_time, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_remain_renew_time, test_l1_dhcp4c_get_ecm_remain_rebind_time_positive1, test_l1_dhcp4c_get_ecm_remain_rebind_time_negative1, test_l1_dhcp4cApi_hal_positive1_get_ecm_config_attempts, test_l1_dhcp4cApi_hal_negative1_get_ecm_config_attempts, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_ifname, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_ifname, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_fsm_state, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_fsm_state, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_ip_addr, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_ip_addr, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_mask, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_mask, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_gw, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_gw, test_l1_dhcp4cApi_hal_positive2_dhcp4c_get_ecm_dns_svrs, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_dns_svrs, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_ecm_dhcp_svr, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_ecm_dhcp_svr, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_emta_remain_lease_time, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_emta_remain_lease_time, test_l1_dhcp4cApi_hal_positive1_get_emta_remain_renew_time, test_l1_dhcp4cApi_hal_negative1_get_emta_remain_renew_time, test_l1_dhcp4cApi_hal_positive1_dhcp4c_get_emta_remain_rebind_time, test_l1_dhcp4cApi_hal_negative1_dhcp4c_get_emta_remain_rebind_time };
    // Add tests to the suite
    for (int i = 0; i < sizeof(list1) / sizeof(list1[0]); i++) {
        UT_add_test(pSuite, list1[i], list2[i]);
    }
    return 0;
}
int main(int argc, char** argv)
{
    int registerReturn = 0;
    /* Register tests as required, then call the UT-main to support switches and triggering */
    UT_init( argc, argv );
    /* Check if tests are registered successfully */
    registerReturn = register_hal_tests();
    if (registerReturn == 0)
    {
        printf("register_hal_tests() returned success");
    }
    else
    {
        printf("register_hal_tests() returned failure");
        return 1;
    }
    /* Begin test executions */
    UT_run_tests();
    return 0;
}
