
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
* @file test_dhcpv4c_api.c
* @page dhcpv4c_api Level 1 Tests
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios).
* This is to ensure that the dhcpv4c_api APIs meet the requirements across all vendors.
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None @n@n
*
* Ref to API Definition specification documentation : [halSpec.md](../../../docs/halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include <sys/socket.h>
#include "dhcpv4c_api.h"
#include <netinet/in.h> // for inet_aton
#include <arpa/inet.h>  // for htonl and ntohl

struct in_addr addr;

/**
* @brief function to check whether ip address is in valid range or not
**/
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
    }
    else {
        return 0; // IP is not in range
    }
}

/**
 * @brief Test case to verify the functionality of dhcpv4c_get_ert_lease_time function
 *
 * This test case verifies the functionality of the dhcpv4c_get_ert_lease_time function by checking if the return value is STATUS_SUCCESS and if the value of pValue is within the valid range.
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
 * In the below table, each row represents a step/variation for this test case.
 *
 * | Variation / Step | Description | Test Data | Expected Result | Notes |
 * | :--------------: | ----------- | --------- | --------------- | ----- |
 * |       01         |Invoking dhcpv4c_get_ert_lease_time with valid memory location| *pValue = valid pointer | STATUS_SUCCESS | Should be successful |
 */
void test_l1_dhcpv4c_api_positive1_GetValidLeaseTime(void) {
    UINT value;    	
    UT_LOG("Entering test_l1_dhcpv4c_api_positive1_GetValidLeaseTime...");
    
    UT_LOG("Invoking dhcpv4c_get_ert_lease_time...");
    INT status = dhcpv4c_get_ert_lease_time(&value);

    UT_LOG("Return status: %d", status);
    UT_LOG("Return value: %u", value);	
    // Check if the return value is STATUS_SUCCESS
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    // Check if the value of pValue is within the valid range
    if(value >= 60 && value <= 604800)
    {
        UT_LOG("ert_lease_time is %u which is a valid value.", value);
        UT_PASS("dhcpv4c_get_ert_lease_time validation success");
    }
    else
    {
        UT_LOG("ert_lease_time is %u which is a invalid value.", value);
        UT_FAIL("dhcpv4c_get_ert_lease_time validation failed");		
    }

    UT_LOG("Exiting test_l1_dhcpv4c_api_positive1_GetValidLeaseTime...");
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
void test_l1_dhcpv4c_api_negative1_InvalidPointer(void) {
    UT_LOG("Entering test_l1_dhcpv4c_api_negative1_InvalidPointer...");

    UT_LOG("Invoking dhcpv4c_get_ert_lease_time with NULL pointer...");
    INT status = dhcpv4c_get_ert_lease_time(NULL);

    UT_LOG("Return status: %d", status);
    // Check if the return value is STATUS_FAILURE
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG("Exiting test_l1_dhcpv4c_api_negative1_InvalidPointer...");
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
void test_l1_dhcpv4c_positive_1_get_ert_remain_lease_time(void)
{
    UINT leaseTime;
    UT_LOG("Entering test_l1_dhcpv4c_positive_1_get_ert_remain_lease_time...");
  
    UT_LOG("Invoking dhcpv4c_get_ert_remain_lease_time with a valid pointer");
    int status = dhcpv4c_get_ert_remain_lease_time(&leaseTime);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    UT_LOG("Return status: %d", status);	
    UT_LOG("Lease Time: %u", leaseTime);

    if(leaseTime >= 0 && leaseTime <= 4294967295)
    {
        UT_LOG("leaseTime is %u which is a valid value.", leaseTime);
        UT_PASS("dhcpv4c_get_ert_remain_lease_time validation success");
    }
    else
    {
	UT_LOG("leaseTime is %u which is a invalid value.", leaseTime);
        UT_FAIL("dhcpv4c_get_ert_remain_lease_time validation failed");		
    }

    UT_LOG("Exiting test_l1_dhcpv4c_positive_1_get_ert_remain_lease_time...");
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
void test_l1_dhcpv4c_negative_1_get_ert_remain_lease_time(void)
{
    UT_LOG("Entering test_l1_dhcpv4c_negative_1_get_ert_remain_lease_time...");
    UT_LOG("Invoking dhcpv4c_get_ert_remain_lease_time with a NULL pointer");
    int status = dhcpv4c_get_ert_remain_lease_time(NULL); 
    UT_LOG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcpv4c_negative_1_get_ert_remain_lease_time...");
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
    * | 01 | Invoking dhcpv4c_get_ert_remain_renew_time with valid memory address for pValue. | Value = valid memory address |STATUS_SUCCESS | Value's range should retrieved successfully and within the range 0 to (2^32)-1 |
    */

void test_l1_dhcpv4c_get_ert_remain_renew_time_positive_1_valid_memory_address_passed(void)
{
    UINT value;
    UT_LOG("Entering test_l1_dhcpv4c_get_ert_remain_renew_time_positive_1_valid_memory_address_passed...");
    
    UT_LOG("Invoking dhcpv4c_get_ert_remain_renew_time with valid memory address for pValue.");
    INT status = dhcpv4c_get_ert_remain_renew_time(&value);

    UT_LOG("Return status: %d", status);
    UT_LOG("Return value: %u", value);	
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if(value >= 0 && value <= 4294967295){
	UT_LOG("ert_remain_renew_time is %u which is a valid value.", value);
        UT_PASS("dhcpv4c_get_ert_remain_renew_time validation success");
    }
    else{
        UT_LOG("ert_remain_renew_time is %u which is a invalid value.", value);
        UT_FAIL("dhcpv4c_get_ert_remain_renew_time validation failed");		
    }

    UT_LOG("Exiting test_l1_dhcpv4c_get_ert_remain_renew_time_positive_1_valid_memory_address_passed...");
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
void test_l1_dhcpv4c_get_ert_remain_renew_time_negative_1_null_pointer_passed(void)
{
    UT_LOG("Entering test_l1_dhcpv4c_get_ert_remain_renew_time_negative_1_null_pointer_passed...");
    UT_LOG("Invoking dhcpv4c_get_ert_remain_renew_time with NULL pointer for pValue.");
    INT status = dhcpv4c_get_ert_remain_renew_time(NULL);
    UT_LOG("Return value: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcpv4c_get_ert_remain_renew_time_negative_1_null_pointer_passed...");
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
* | 01 | Invoking dhcpv4c_get_ert_remain_rebind_time with valid pValue pointer. | Value = valid memory address | STATUS_SUCCESS |  Value's range should retrieved successfully and within the range 0 to (2^32)-1 |
*/

void test_l1_dhcpv4c_api_positive1_get_ert_remain_rebind_time(void) {
    UINT timeValue;
    UT_LOG("Entering test_l1_dhcpv4c_api_positive1_get_ert_remain_rebind_time...");

    UT_LOG("Invoking dhcpv4c_get_ert_remain_rebind_time with valid pValue pointer.");
    INT status = dhcpv4c_get_ert_remain_rebind_time(&timeValue);

    UT_LOG("Return Status: %d", status);
    UT_LOG("Return value: %u", timeValue);    
    // Check the return status and time value
    UT_ASSERT_EQUAL(STATUS_SUCCESS, status);
    if(timeValue >= 0 && timeValue <= 4294967295){
        UT_LOG("ert_remain_rebind_time is %u which is a valid value.", timeValue);
        UT_PASS("dhcpv4c_get_ert_remain_rebind_time validation success");
    }
    else{
        UT_LOG("ert_remain_rebind_time is %u which is a invalid value.", timeValue);
        UT_FAIL("dhcpv4c_get_ert_remain_rebind_time validation failed");		
    }
    UT_LOG("Exiting test_l1_dhcpv4c_api_positive1_get_ert_remain_rebind_time...");
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
void test_l1_dhcpv4c_api_negative1_get_ert_remain_rebind_time(void) {
    UINT *pValue = NULL;
    UT_LOG("Entering test_l1_dhcpv4c_api_negative1_get_ert_remain_rebind_time...");

    // Invalid pValue pointer
    UT_LOG("Invoking dhcpv4c_get_ert_remain_rebind_time with NULL pValue pointer.");
    INT status = dhcpv4c_get_ert_remain_rebind_time(pValue);

    UT_LOG("Return Status: %d", status);

    // Check the return status
    UT_ASSERT_EQUAL(STATUS_FAILURE, status);

    UT_LOG("Exiting test_l1_dhcpv4c_api_negative1_get_ert_remain_rebind_time...");
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
* | 01 | Invoking dhcpv4c_get_ert_config_attempts with pValue = &someInteger | *pValue = valid pointer | STATUS_SUCCESS | The function should successfully retrieve the number of attempts made |
*/
void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_config_attempts_validPointer_successfulCall(void) {
    INT someInteger = 0;
    INT status;

    UT_LOG("Entering test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_config_attempts_validPointer_successfulCall...");
    UT_LOG("Invoking dhcpv4c_get_ert_config_attempts with pValue = &someInteger");
    status = dhcpv4c_get_ert_config_attempts(&someInteger);
    UT_LOG("Return status: %d", status);
    UT_LOG("Return value: %d", someInteger);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if(someInteger >= -2147483648 && someInteger <= 2147483647){
        UT_LOG("ert_config_attempts is %d which is a valid value.", someInteger);
        UT_PASS("dhcpv4c_get_ert_config_attempts validation success");
    }
    else{
        UT_LOG("ert_config_attempts is %d which is a invalid value.", someInteger);
        UT_FAIL("dhcpv4c_get_ert_config_attempts validation failed");		
    }		
    UT_LOG("Exiting test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_config_attempts_validPointer_successfulCall...");
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
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_config_attempts_nullPointer(void) {
    INT *pValue = NULL;
    INT status;

    UT_LOG("Entering test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_config_attempts_nullPointer...");
    UT_LOG("Invoking dhcpv4c_get_ert_config_attempts with pValue = NULL");
    status = dhcpv4c_get_ert_config_attempts(pValue);

    UT_LOG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    UT_LOG("Exiting test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_config_attempts_nullPointer...");
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

void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_ifname(void) {
    CHAR pName[64] = {0};
    UT_LOG("Entering test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_ifname...");
    UT_LOG("Invoking dhcpv4c_get_ert_ifname with a valid memory location");
    int status = dhcpv4c_get_ert_ifname(pName);

    UT_LOG("Return status: %d", status);
    UT_LOG("Return value : %s ", pName);	
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    UT_LOG("Exiting test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_ifname...");	
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
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_ifname(void) {
    CHAR *pName = NULL;
    UT_LOG("Entering test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_ifname...");

    UT_LOG("Invoking dhcpv4c_get_ert_ifname with null pointer for pName");
    INT status = dhcpv4c_get_ert_ifname(pName);

    UT_LOG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG("Exiting test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_ifname...");
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
void test_l1_dhcpv4c_api_positive_1_dhcpv4c_get_ert_fsm_state(void) {
    INT value;
    UT_LOG("Entering test_l1_dhcpv4c_api_positive_1_dhcpv4c_get_ert_fsm_state...");

    // Allocate memory location
    UT_LOG("Invoking dhcpv4c_get_ert_fsm_state() with valid memory location...");
    // Call dhcpv4c_get_ert_fsm_state()
    int status = dhcpv4c_get_ert_fsm_state(&value);

    // Check the return status and the value of pValue

    UT_LOG("Return status: %d", status);
    UT_LOG("Return value: %d", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if(value >= 1 && value <= 6){
        UT_LOG("ert_fsm_state is %d which is a valid value.", value);
        UT_PASS("dhcpv4c_get_ert_fsm_state validation success");
    }
    else{
        UT_LOG("ert_fsm_state is %d which is a invalid value.", value);
        UT_FAIL("dhcpv4c_get_ert_fsm_state validation failed");		
    }
    UT_LOG("Exiting test_l1_dhcpv4c_api_positive_1_dhcpv4c_get_ert_fsm_state...");
}

/**
* @brief This test case checks for the negative scenario when NULL pointer is provided as an argument to dhcpv4c_get_ert_fsm_state() function.
*
* This test case verifies that the function dhcpv4c_get_ert_fsm_state() returns STATUS_FAILURE when a NULL pointer is provided as an argument.
*
* **Test Group ID:** Basic (for L1): 01
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
void test_l1_dhcpv4c_api_negative_3_dhcpv4c_get_ert_fsm_state(void) {
    UT_LOG("Entering test_l1_dhcpv4c_api_negative_3_dhcpv4c_get_ert_fsm_state...");

    // Call dhcpv4c_get_ert_fsm_state() with NULL pointer
    UT_LOG("Invoking dhcpv4c_get_ert_fsm_state() with NULL pointer...");
    int status = dhcpv4c_get_ert_fsm_state(NULL);
    UT_LOG("Return status: %d", status);
    // Check the return status
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG("Exiting test_l1_dhcpv4c_api_negative_3_dhcpv4c_get_ert_fsm_state...");
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
* | 01 | Invoking dhcpv4c_get_ert_ip_addr with valid memory location for pValue | *pValue = valid pointer | STATUS_SUCCESS | ipAddr should be in the range 1 to 223255255  Should be successful |
*/
 
void test_l1_dhcpv4c_positive_1_dhcpv4c_get_ert_ip_addr(void) {
    char ip_str[20];
    UINT ipAddr;
    UT_LOG("Entering test_l1_dhcpv4c_positive_1_dhcpv4c_get_ert_ip_addr...");

    /* Test with a valid memory location as the pValue argument */
    UT_LOG("Invoking dhcpv4c_get_ert_ip_addr with valid memory location for pValue");
    INT status = dhcpv4c_get_ert_ip_addr(&ipAddr);

    /* Test description */
    UT_LOG("Return status: %d", status);
    UT_LOG("Return value before modification : %u", ipAddr);
    /* Verify return status */
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    addr.s_addr = ipAddr ;
    strcpy(ip_str,inet_ntoa(addr));
	
    UT_LOG("Return value: %s", ip_str);
    /* Verify IP address falls within valid ranges */
    if(isIpAddressInRange(ip_str,"1.0.0.0","127.0.0.0") || isIpAddressInRange(ip_str,"128.0.0.0","191.255.0.0") || isIpAddressInRange(ip_str,"192.0.0.0","223.255.255.0")){
        UT_LOG("ert_ip_addr is %s which is a valid value.", ip_str);
        UT_PASS("dhcpv4c_get_ert_ip_addr validation success");
    }
    else{
        UT_LOG("ert_ip_addr is %s which is a invalid value.", ip_str);
        UT_FAIL("dhcpv4c_get_ert_ip_addr validation failed");
    }

    UT_LOG("Exiting test_l1_dhcpv4c_positive_1_dhcpv4c_get_ert_ip_addr...");
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
void test_l1_dhcpv4c_negative_1_dhcpv4c_get_ert_ip_addr(void) {
    UT_LOG("Entering test_l1_dhcpv4c_negative_1_dhcpv4c_get_ert_ip_addr...");
    UT_LOG("Invoking dhcpv4c_get_ert_ip_addr with null pointer for pValue");
    /* Test with a null pointer for pValue argument */
    INT status = dhcpv4c_get_ert_ip_addr(NULL);

    /* Test description */
    UT_LOG("Return status: %d", status);
    /* Verify return status */
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG("Exiting test_l1_dhcpv4c_negative_1_dhcpv4c_get_ert_ip_addr...");
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
void test_l1_dhcpv4c_api_positive_1_get_ert_mask(void) {
    UINT value;
    unsigned char octet1 = 0;
    unsigned char octet2 = 0;
    unsigned char octet3 = 0;
    unsigned char octet4 = 0;
    UT_LOG("Entering test_l1_dhcpv4c_api_positive_1_get_ert_mask...");
    // Invoke API
    UT_LOG("Invoking dhcpv4c_get_ert_mask with valid pValue...");
    INT status = dhcpv4c_get_ert_mask(&value);

    // Verify result
    UT_LOG("Return Status: %d", status);
    UT_LOG("Output: pValue = %u", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    octet1 = (value >> 24) & 0xFF;
    octet2 = (value >> 16) & 0xFF;
    octet3 = (value >> 8) & 0xFF;
    octet4 = value & 0xFF;
    if((octet1 >=0 && octet1 <= 255) && (octet2 >=0 && octet2 <= 255) && (octet3 >=0 && octet3 <= 255) && (octet4 >=0 && octet4 <= 255)){
        UT_LOG("octet1 is %u, octet2 is %u, octet3 is %u, octet4 is %u which are  valid values.",octet1,octet2,octet3,octet4 );
        UT_PASS("dhcpv4c_get_ert_mask validation success");
    }
    else{
        UT_LOG("octet1 is %c, octet2 is %c, octet3 is %c, octet4 is %c . there is one invalid value",octet1,octet2,octet3,octet4 );
        UT_FAIL("dhcpv4c_get_ert_mask validation failed");		
    }		
    UT_LOG("Exiting test_l1_dhcpv4c_api_positive_1_get_ert_mask...");
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
 *
 */
void test_l1_dhcpv4c_api_negative_1_get_ert_mask(void) {
    UINT *pValue = NULL; 
    UT_LOG("Entering test_l1_dhcpv4c_api_negative_1_get_ert_mask...");
    // Test input
    UT_LOG("Invoking dhcpv4c_get_ert_mask with NULL pValue pointer...");    
    // Invoke API
    INT status = dhcpv4c_get_ert_mask(pValue);
    
    // Verify result
    UT_LOG("Return Status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    
    UT_LOG("Exiting test_l1_dhcpv4c_api_negative_1_get_ert_mask...");
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

void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_gw(void) {
    UINT value;
    char ip_str[20];
    UT_LOG("Entering test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_gw...");
    // Provide a valid memory location for pValue
    UT_LOG("Invoking dhcpv4c_get_ert_gw with valid memory location for pValue");
    INT status = dhcpv4c_get_ert_gw(&value);

    // Check the return status
    UT_LOG("Return status: %d", status);
    UT_LOG("Return value: %u", value);
    UT_ASSERT_EQUAL(STATUS_SUCCESS, status);
    addr.s_addr = value ;
    strcpy(ip_str,inet_ntoa(addr));
	
    UT_LOG("Return value after modification: %s", ip_str);
    /* Verify IP address falls within valid ranges */
    if(isIpAddressInRange(ip_str,"1.0.0.0","127.0.0.0") || isIpAddressInRange(ip_str,"128.0.0.0","191.255.0.0") || isIpAddressInRange(ip_str,"192.0.0.0","223.255.255.0")){
        UT_LOG("ert_gw is %s which is a valid value.", ip_str);
        UT_PASS("dhcpv4c_get_ert_gw validation success");
    }
    else{
        UT_LOG("ert_gw is %s which is a invalid value.", ip_str);
        UT_FAIL("dhcpv4c_get_ert_gw validation failed");
    }
    UT_LOG("Exiting test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_gw...");
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
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_gw(void) {
    UT_LOG("Entering test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_gw...");
    UT_LOG("Invoking dhcpv4c_get_ert_gw with NULL pointer for pValue");
    // Provide NULL pointer for pValue
    INT status = dhcpv4c_get_ert_gw(NULL);

    // Check the return status
    UT_LOG("Return status: %d", status);
    UT_ASSERT_EQUAL(STATUS_FAILURE, status);

    UT_LOG("Exiting test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_gw...");
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
    char ip_str[20];
    int dns_svrs;
    dhcpv4c_ip_list_t ip_list;
    UT_LOG("Entering test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_dns_svrs...");

    memset(&ip_list, 0, sizeof(dhcpv4c_ip_list_t));
    UT_LOG("Invoking dhcpv4c_get_ert_dns_svrs with valid memory for dhcpv4c_ip_list_t");
    INT status = dhcpv4c_get_ert_dns_svrs(&ip_list);

    UT_LOG("Return status: %d", status);
    UT_LOG("Number of IP addresses: %d", ip_list.number);
    UT_LOG("First IP address: %u.%u.%u.%u", ip_list.addrs[0], ip_list.addrs[1], ip_list.addrs[2], ip_list.addrs[3]);

    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if((ip_list.number >= -2147483648)&&(ip_list.number <= 2147483647))
    {
        UT_LOG("number of ert_dns_svrs is %d which is a valid value.", ip_list.number);
        UT_PASS("dhcpv4c_get_ert_dns_svrs validation success");
    }
    else{
        UT_LOG("number of ert_dns_svrs is %d which is a invalid value.", ip_list.number);
        UT_FAIL("dhcpv4c_get_ert_dns_svrs validation failed");		
    }
    for(dns_svrs = 0; dns_svrs < ip_list.number; dns_svrs++){
        memset(ip_str, 0, sizeof(ip_str));
        memset(&addr, 0, sizeof(addr));	
        addr.s_addr = ip_list.addrs[dns_svrs] ;
        strcpy(ip_str,inet_ntoa(addr));
	
        UT_LOG("Return value after modification: %s", ip_str);
        /* Verify IP address falls within valid ranges */
        if(isIpAddressInRange(ip_str,"1.0.0.0","127.0.0.0") || isIpAddressInRange(ip_str,"128.0.0.0","191.255.0.0") || isIpAddressInRange(ip_str,"192.0.0.0","223.255.255.0")){
            UT_LOG("ert_dns_svrs is %s which is a valid value.", ip_str);
            UT_PASS("dhcpv4c_get_ert_dns_svrs validation success");
        }
        else{
            UT_LOG("ert_dns_svrs is %s which is a invalid value.", ip_str);
            UT_FAIL("dhcpv4c_get_ert_dns_svrs validation failed");
        }
    }
    UT_LOG("Exiting test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_dns_svrs...");
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

void test_l1_dhcpv4c_api_negative1_invalid_memory_for_dhcpv4c_ip_list_t(void)
{
    dhcpv4c_ip_list_t *pList = NULL;
    UT_LOG("Entering test_l1_dhcpv4c_api_negative1_invalid_memory_for_dhcpv4c_ip_list_t...");
    UT_LOG("Invoking dhcpv4c_get_ert_dns_svrs with null pointer");
    INT status = dhcpv4c_get_ert_dns_svrs(pList);

    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG("Exiting test_l1_dhcpv4c_api_negative1_invalid_memory_for_dhcpv4c_ip_list_t...");
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
void test_l1_dhcpv4c_api_positive_1_get_ert_dhcp_svr(void) {
    char ip_str[20];
    UINT value;
    UT_LOG("Entering test_l1_dhcpv4c_api_positive_1_get_ert_dhcp_svr...");
    UT_LOG("Invoking dhcpv4c_get_ert_dhcp_svr with valid memory address provided");
    INT status = dhcpv4c_get_ert_dhcp_svr(&value);
    UT_LOG("Return Status: %d", status);
    UT_LOG("Output Value: %u", value);

    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    addr.s_addr = value;
    strcpy(ip_str,inet_ntoa(addr));
	
    UT_LOG("Return value after modification: %s", ip_str);
    /* Verify IP address falls within valid ranges */
    if(isIpAddressInRange(ip_str,"1.0.0.0","127.0.0.0") || isIpAddressInRange(ip_str,"128.0.0.0","191.255.0.0") || isIpAddressInRange(ip_str,"192.0.0.0","223.255.255.0")){
        UT_LOG("ert_dhcp_svr is %s which is a valid value.", ip_str);
        UT_PASS("dhcpv4c_get_ert_dhcp_svr validation success");
    }
    else{
        UT_LOG("ert_dhcp_svr is %s which is a invalid value.", ip_str);
        UT_FAIL("dhcpv4c_get_ert_dhcp_svr validation failed");
    }
    UT_LOG("Exiting test_l1_dhcpv4c_api_positive_1_get_ert_dhcp_svr...");
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
void test_l1_dhcpv4c_api_negative_1_dhcpv4c_get_ert_dhcp_svr(void) {
    UT_LOG("Entering test_l1_dhcpv4c_api_negative_1_dhcpv4c_get_ert_dhcp_svr...");

    UT_LOG("Invoking dhcpv4c_get_ert_dhcp_svr with null pointer provided");
    INT status = dhcpv4c_get_ert_dhcp_svr(NULL);

    UT_LOG("Return Status: %d", status);

    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG("Exiting test_l1_dhcpv4c_api_negative_1_dhcpv4c_get_ert_dhcp_svr...");
}

/**
 * @brief Test the API dhcpv4c_get_ecm_lease_time with valid pValue
 *
 * This test case checks the functionality of dhcpv4c_get_ecm_lease_time
 * API when called with a valid pValue. It verifies that the correct output
 * value is returned and the return status is success.
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
void test_l1_dhcpv4c_api_positive_1_get_ecm_lease_time(void) {
    UINT value;
    UT_LOG("Entering test_l1_dhcpv4c_api_positive_1_get_ecm_lease_time...");
 
    UT_LOG("Invoking dhcpv4c_get_ecm_lease_time with valid pValue");
    INT result = dhcpv4c_get_ecm_lease_time(&value);
  
    UT_LOG("Return Status: %d", result);
    UT_LOG("Output Value: %u", value);

  
    UT_ASSERT_EQUAL(result, STATUS_SUCCESS);
    if(value >= 60 && value <= 604800){
	UT_LOG("ecm_lease_time is %u which is a valid value.", value);
        UT_PASS("dhcpv4c_get_ecm_lease_time validation success");
    }
    else{
        UT_LOG("ecm_lease_time is %u which is a invalid value.", value);
        UT_FAIL("dhcpv4c_get_ecm_lease_time validation failed");		
    }
  
    UT_LOG("Exiting test_l1_dhcpv4c_api_positive_1_get_ecm_lease_time...");
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
 * | :--------------: | ----------- | --------- | --------------- | ----- |
 * |       01         | Invoking dhcpv4c_get_ecm_lease_time with NULL pointer | pValue = NULL | STATUS_FAILURE | Should be unsuccessful |
 */
void test_l1_dhcpv4c_api_negative_1_get_ecm_lease_time(void) {
    UT_LOG("Entering test_l1_dhcpv4c_api_negative_1_get_ecm_lease_time...");

    UT_LOG("Invoking dhcpv4c_get_ecm_lease_time with NULL pValue");
    INT result = dhcpv4c_get_ecm_lease_time(NULL);

    UT_LOG("Return Status: %d", result);

    UT_ASSERT_EQUAL(result, STATUS_FAILURE);

    UT_LOG("Exiting test_l1_dhcpv4c_api_negative_1_get_ecm_lease_time...");
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
void test_l1_dhcpv4c_positive1_get_ecm_remain_lease_time() {
    UINT value;
    
    UT_LOG("Entering test_l1_dhcpv4c_positive1_get_ecm_remain_lease_time...");
    
    // Invoke the API with a valid pointer
    UT_LOG("Invoking dhcpv4c_get_ecm_remain_lease_time with a valid pointer...");
    INT status = dhcpv4c_get_ecm_remain_lease_time(&value);
    
    // Check the return value and the retrieved lease time
    UT_LOG("Returned status: %d", status);
    UT_LOG("Retrieved lease time: %u", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if(value >=0 && value <= 4294967295){
        UT_LOG("ecm_remain_lease_time is %u which is a valid value.", value);
        UT_PASS("dhcpv4c_get_ecm_remain_lease_time validation success");
    }
    else{
        UT_LOG("ecm_remain_lease_time is %u which is a invalid value.", value);
        UT_FAIL("dhcpv4c_get_ecm_remain_lease_time validation failed");		
    }
    UT_LOG("Exiting test_l1_dhcpv4c_positive1_get_ecm_remain_lease_time...");
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
void test_l1_dhcpv4c_negative1_get_ecm_remain_lease_time() {
    UT_LOG("Entering test_l1_dhcpv4c_negative1_get_ecm_remain_lease_time...");

    // Invoke the API with a null pointer
    UT_LOG("Invoking dhcpv4c_get_ecm_remain_lease_time with a null pointer...");
    INT status = dhcpv4c_get_ecm_remain_lease_time(NULL);

    // Check the return value
    UT_LOG("Returned status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG("Exiting test_l1_dhcpv4c_negative1_get_ecm_remain_lease_time...");
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
 * | 01 |Invoke dhcpv4c_get_ecm_remain_renew_time with valid memory  | *pValue = valid memory location | STATUS_SUCCESS | Value of pValue should be in the range of 0 to (pow(2, 32) - 1) |
 */
void test_l1_dhcpv4c_get_ecm_remain_renew_time_positive_1_default_case(void)
{
    UINT value;
    UT_LOG("Entering test_l1_dhcpv4c_get_ecm_remain_renew_time_positive_1_default_case...");
    UT_LOG("Invoking dhcpv4c_get_ecm_remain_renew_time with a valid memory location");
    INT status = dhcpv4c_get_ecm_remain_renew_time(&value);
    UT_LOG("Return status: %d", status);
    UT_LOG("Return value: %u", value);
    // Check the return status
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    // Check the value of pValue
    if(value >= 0 && value <= 4294967295){
        UT_LOG("ecm_remain_renew_time is %u which is a valid value.", value);
        UT_PASS("dhcpv4c_get_ecm_remain_renew_time validation success");
    }
    else{
        UT_LOG("ecm_remain_renew_time is %u which is a invalid value.", value);
        UT_FAIL("dhcpv4c_get_ecm_remain_renew_time validation failed");		
    }

    UT_LOG("Exiting test_l1_dhcpv4c_get_ecm_remain_renew_time_positive_1_default_case...");
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
void test_l1_dhcpv4c_get_ecm_remain_renew_time_negative_1_null_pointer(void)
{
    UT_LOG("Entering test_l1_dhcpv4c_get_ecm_remain_renew_time_negative_1_null_pointer...");

    UT_LOG("Invoking dhcp4c_get_ert_lease_time with NULL");
    INT status = dhcpv4c_get_ecm_remain_renew_time(NULL);
    UT_LOG("Return status: %d", status);

    // Check the return status
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG("Exiting test_l1_dhcpv4c_get_ecm_remain_renew_time_negative_1_null_pointer...");
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
* | 01 | Invoking dhcpv4c_get_ecm_remain_rebind_time with valid pValue | *pValue = valid memory location | STATUS_SUCCESS | The value should be between 0 and UINT_MAX |
*/
void test_l1_dhcpv4c_api_positive_1_ecm_remain_rebind_time(void)
{
    UINT value;
    UT_LOG("Entering test_l1_dhcpv4c_api_positive_1_ecm_remain_rebind_time...");
    UT_LOG("Invoking dhcpv4c_get_ecm_remain_rebind_time with valid pValue.");
    INT status = dhcpv4c_get_ecm_remain_rebind_time(&value);

    UT_LOG("Return status: %d", status);
    UT_LOG("Return pValue: %u", value);

    UT_ASSERT_EQUAL(STATUS_SUCCESS, status);
    if(value >= 0 && value <= 4294967295){
        UT_LOG("ecm_remain_rebind_time is %d which is a valid value.", value);
        UT_PASS("dhcpv4c_get_ecm_remain_rebind_time validation success");
    }
    else{
        UT_LOG("ecm_remain_rebind_time is %d which is a invalid value.", value);
        UT_FAIL("dhcpv4c_get_ecm_remain_rebind_time validation failed");		
    }

    UT_LOG("Exiting test_l1_dhcpv4c_api_positive_1_ecm_remain_rebind_time...");
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
void test_l1_dhcpv4c_api_negative_1_get_ecm_remain_rebind_time(void)
{
    UT_LOG("Entering test_l1_dhcpv4c_api_negative_1_get_ecm_remain_rebind_time...");

    UT_LOG("Invoking dhcpv4c_get_ecm_remain_rebind_time with NULL pValue.");
    INT status = dhcpv4c_get_ecm_remain_rebind_time(NULL);

    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(STATUS_FAILURE, status);

    UT_LOG("Exiting test_l1_dhcpv4c_api_negative_1_get_ecm_remain_rebind_time...");
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
void test_l1_dhcpv4c_api_positive_1_get_ecm_config_attempts(void)
{
    INT value;
    UT_LOG("Entering test_l1_dhcpv4c_api_positive_1_get_ecm_config_attempts...");
    UT_LOG("Invoking dhcpv4c_get_ecm_config_attempts with valid pointer");
    INT ret = dhcpv4c_get_ecm_config_attempts(&value);

    UT_LOG("Return status: %d", ret);
    UT_LOG("Return value: %d", value);
    UT_ASSERT_EQUAL(ret, STATUS_SUCCESS);
    if(value >= -2147483648 && value <= 2147483647){
        UT_LOG("ecm_config_attempts is %d which is a valid value.", value);
        UT_PASS("dhcpv4c_get_ecm_config_attempts validation success");
    }
    else{
        UT_LOG("ecm_config_attempts is %d which is a invalid value.", value);
        UT_FAIL("dhcpv4c_get_ecm_config_attempts validation failed");		
    }

    UT_LOG("Exiting test_l1_dhcpv4c_api_positive_1_get_ecm_config_attempts...");
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
void test_l1_dhcpv4c_api_negative_1_ecm_config_attempts(void)
{
    INT *pValue = NULL;
    UT_LOG("Entering test_l1_dhcpv4c_api_negative_1_ecm_config_attempts...");
    UT_LOG("Invoking dhcpv4c_get_ecm_config_attempts with NULL pointer");
    INT ret = dhcpv4c_get_ecm_config_attempts(pValue);

    UT_LOG("Return status: %d", ret);
    UT_ASSERT_EQUAL(ret, STATUS_FAILURE);

    UT_LOG("Exiting test_l1_dhcpv4c_api_negative_1_ecm_config_attempts...");
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
    CHAR pName[64];
    UT_LOG("Entering test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_ifname...");
    // Allocate a 64-byte CHAR array
    UT_LOG("Invoking dhcpv4c_get_ecm_ifname with pName as valid memory location. Expected Output: STATUS_SUCCESS");
    // Invoke the API
    INT status = dhcpv4c_get_ecm_ifname(pName);
    UT_LOG("Return status: %d", status);
    UT_LOG("Return value: %s", pName);
    // Check the return value
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    UT_LOG("Exiting test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_ifname...");
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
void test_l1_dhcpv4c_api_negative1_get_ecm_ifname(void)
{
    UT_LOG("Entering test_l1_dhcpv4c_api_negative1_get_ecm_ifname...");
    UT_LOG("Invoking dhcpv4c_get_ecm_ifname with pName as NULL. Expected Output: STATUS_FAILURE");
    // Invoke the API with pName as NULL
    INT status = dhcpv4c_get_ecm_ifname(NULL);

    UT_LOG("Return status: %d", status);
    // Check the return value
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);


    UT_LOG("Exiting test_l1_dhcpv4c_api_negative1_get_ecm_ifname...");
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

void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_fsm_state(void) {
    INT value = 0;
    UT_LOG("Entering test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_fsm_state...");
    UT_LOG("Invoking dhcpv4c_get_ecm_fsm_state with valid pointer");
    INT status = dhcpv4c_get_ecm_fsm_state(&value);

    UT_LOG("Return status: %d", status);
    UT_LOG("Return value: %d", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if(value >= 1 && value <= 6){
        UT_LOG("ecm_fsm_state is %d which is a valid value.", value);
        UT_PASS("dhcpv4c_get_ecm_fsm_state validation success");
    }
    else{
        UT_LOG("ecm_fsm_state is %d which is a invalid value.", value);
        UT_FAIL("dhcpv4c_get_ecm_fsm_state validation failed");		
    }

    UT_LOG("Exiting test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_fsm_state...");
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
 * | Variation / Step | Description                                       | Test Data     | Expected Result                   | Notes              |
 * | :--------------: | ------------------------------------------------- | ------------- | --------------------------------- | ------------------ |
 * |       01         | Invoking dhcpv4c_get_ecm_fsm_state with pValue = NULL  | pValue = NULL | STATUS_FAILURE | Should fail with STATUS_FAILURE |
 *
 */
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_fsm_state(void) {
    INT *pValue = NULL;
    UT_LOG("Entering test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_fsm_state...");
    UT_LOG("Invoking dhcpv4c_get_ecm_fsm_state with NULL");
    INT status = dhcpv4c_get_ecm_fsm_state(pValue);

    UT_LOG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);


    UT_LOG("Exiting test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_fsm_state...");
}

/**
* @brief Test the functionality of the dhcpv4c_get_ecm_ip_addr function
*
* This test validates the dhcpv4c_get_ecm_ip_addr function by invoking it with a valid UINT pointer. 
* It checks the status of the function call and the IP address returned by the function. 
* The test ensures that the status is STATUS_SUCCESS and the IP address is within the range of valid IP addresses.
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

void test_l1_dhcpv4c_positive1_GetEcmIpAddress(void) {
    char ip_str[20];
    UINT ipAddr;
    UT_LOG("Entering test_l1_dhcpv4c_positive1_GetEcmIpAddress...");
    UT_LOG("Invoking dhcpv4c_get_ecm_ip_addr with a valid UINT pointer.");	
    INT status = dhcpv4c_get_ecm_ip_addr(&ipAddr);

    UT_LOG("Return status: %d", status);
    UT_LOG("Return value: %u", ipAddr);

    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    addr.s_addr = ipAddr ;
    strcpy(ip_str,inet_ntoa(addr));
	
    UT_LOG("Return value after modification: %s", ip_str);
    /* Verify IP address falls within valid ranges */
    if(isIpAddressInRange(ip_str,"1.0.0.0","127.0.0.0") || isIpAddressInRange(ip_str,"128.0.0.0","191.255.0.0") || isIpAddressInRange(ip_str,"192.0.0.0","223.255.255.0")){
        UT_LOG("ecm_ip_addr is %s which is a valid value.", ip_str);
        UT_PASS("dhcpv4c_get_ecm_ip_addr validation success");
    }
    else{
        UT_LOG("ecm_ip_addr is %s which is a invalid value.", ip_str);
        UT_FAIL("dhcpv4c_get_ecm_ip_addr validation failed");
    } 
    UT_LOG("Exiting test_l1_dhcpv4c_positive1_GetEcmIpAddress...");
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
void test_l1_dhcpv4c_negative1_GetEcmIpAddress(void) {
    UT_LOG("Entering test_l1_dhcpv4c_negative1_GetEcmIpAddress...");
    UT_LOG("Invoking dhcpv4c_get_ecm_ip_addr with a null pointer.");   
    INT status = dhcpv4c_get_ecm_ip_addr(NULL);
    
    UT_LOG("Status: %d", status);
    
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);
    
    UT_LOG("Exiting test_l1_dhcpv4c_negative1_GetEcmIpAddress...");
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
void test_l1_dhcpv4c_positive1_get_ecm_mask(void)
{
    UINT value;
    INT status;
    unsigned char octet1 = 0;
    unsigned char octet2 = 0;
    unsigned char octet3 = 0;
    unsigned char octet4 = 0;
    /* Log the start of the test */
    UT_LOG("Entering test_l1_dhcpv4c_positive1_get_ecm_mask...");

    /* Invoke the API with valid pValue */
    UT_LOG("Invoking dhcpv4c_get_ecm_mask with valid pointer...");
    status = dhcpv4c_get_ecm_mask(&value);
	
    /* Verify the return status */
    UT_LOG("Return status: %d", status);
    UT_LOG("pValue: %u", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    /* Log the output value */
    octet1 = (value >> 24) & 0xFF;
    octet2 = (value >> 16) & 0xFF;
    octet3 = (value >> 8) & 0xFF;
    octet4 = value & 0xFF;
    if((octet1 >=0 && octet1 <= 255) && (octet2 >=0 && octet2 <= 255) && (octet3 >=0 && octet3 <= 255) && (octet4 >=0 && octet4 <= 255)){
        UT_LOG("octet1 is %u, octet2 is %u, octet3 is %u, octet4 is %u which are  valid values.",octet1,octet2,octet3,octet4 );
        UT_PASS("dhcpv4c_get_ecm_mask validation success");
    }
    else{
        UT_LOG("octet1 is %u, octet2 is %u, octet3 is %u, octet4 is %u . there is one invalid value",octet1,octet2,octet3,octet4 );
        UT_FAIL("dhcpv4c_get_ecm_mask validation failed");		
    }

    /* Log the end of the test */
    UT_LOG("Exiting test_l1_dhcpv4c_positive1_get_ecm_mask...");
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
void test_l1_dhcpv4c_negative1_get_ecm_mask(void)
{
    INT status;

    /* Log the start of the test */
    UT_LOG("Entering test_l1_dhcpv4c_negative1_get_ecm_mask...");

    /* Invoke the API with null pValue */
    UT_LOG("Invoking dhcpv4c_get_ecm_mask with null pValue...");
    status = dhcpv4c_get_ecm_mask(NULL);

    /* Verify the return status */
    UT_LOG("Return status: %d", status);
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    /* Log the end of the test */
    UT_LOG("Exiting test_l1_dhcpv4c_negative1_get_ecm_mask...");
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

void test_l1_dhcpv4c_positive1_dhcpv4c_get_ecm_gw_validOutputMemoryAndStatusCheck( void )
{
    INT status;
    UINT output = 0;
    char ip_str[20];
	
    UT_LOG("Entering test_l1_dhcpv4c_positive1_dhcpv4c_get_ecm_gw_validOutputMemoryAndStatusCheck...");

    // Prepare valid output memory
    UT_LOG("Invoking dhcpv4c_get_ecm_gw with a valid memory location");
    // Invoke the API
    status = dhcpv4c_get_ecm_gw(&output);
    UT_LOG("Return status: %d", status);
    UT_LOG("Return value: %d", output);
    // Verify the status is STATUS_SUCCESS
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);

    addr.s_addr = output ;
    strcpy(ip_str,inet_ntoa(addr));
	
    UT_LOG("Return value after modification: %s", ip_str);
    /* Verify IP address falls within valid ranges */
    if(isIpAddressInRange(ip_str,"1.0.0.0","127.0.0.0") || isIpAddressInRange(ip_str,"128.0.0.0","191.255.0.0") || isIpAddressInRange(ip_str,"192.0.0.0","223.255.255.0")){
        UT_LOG("ecm_gw is %s which is a valid value.", ip_str);
        UT_PASS("dhcpv4c_get_ecm_gw validation success");
    }
    else{
        UT_LOG("ecm_gw is %s which is a invalid value.", ip_str);
        UT_FAIL("dhcpv4c_get_ecm_gw validation failed");
    }		
    UT_LOG("Exiting test_l1_dhcpv4c_positive1_dhcpv4c_get_ecm_gw_validOutputMemoryAndStatusCheck...");
}

/**
* @brief Tests the DHCPv4c_get_ecm_gw function when a null pointer is provided for the output memory
*
* This test case verifies the behavior of the DHCPv4c_get_ecm_gw function when a null pointer is provided for the output memory.
*
* **Test Group ID:** Basic (for L1): 01
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
void test_l1_dhcpv4c_negative1_dhcpv4c_get_ecm_gw_nullPointerProvidedForOutputMemory( void )
{
    INT status;

    UT_LOG("Entering test_l1_dhcpv4c_negative1_dhcpv4c_get_ecm_gw_nullPointerProvidedForOutputMemory...");
    UT_LOG("Invoking dhcpv4c_get_ecm_gw with NULL");
    // Invoke the API with NULL as output memory pointer
    status = dhcpv4c_get_ecm_gw(NULL);
    UT_LOG("Return status: %d", status);
    // Verify the status is STATUS_FAILURE
    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG("Exiting test_l1_dhcpv4c_negative1_dhcpv4c_get_ecm_gw_nullPointerProvidedForOutputMemory...");
}

/**
* @brief Test to verify if a valid memory location is provided to the API.
*
* This test case verifies whether the API 'dhcpv4c_get_ecm_dns_svrs' returns successfully when a valid memory location is provided.
*
* Test Group ID: Basic: 01
* Test Case ID: 045 @n
* Priority: High
*
* Pre-Conditions: None
* Dependencies: None
* User Interaction: If the user chooses to run the test in interactive mode, then the test case has to be selected via console @n
*
* Test Procedure:
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :----: | --------- | ---------- | -------------- | ----- |
* | 01 | Invoking dhcpv4c_get_ecm_dns_svrs with a valid memory location | pList = valid pointer to structure dhcpv4c_ip_list_t | STATUS_SUCCESS | The number of IP addresses should be between 1-4 |
*/
void test_l1_dhcpv4c_api_positive1_get_ecm_dns_svrs(void) {
    char ip_str[20];
    int dns_svrs;
    dhcpv4c_ip_list_t list;
	
    UT_LOG("Entering test_l1_dhcpv4c_api_positive1_get_ecm_dns_svrs...");
    UT_LOG("Invoking dhcpv4c_get_ecm_dns_svrs with a valid memory location");
    INT result = dhcpv4c_get_ecm_dns_svrs(&list);
    UT_LOG("Return status: %d", result);
    UT_ASSERT_EQUAL(result, STATUS_SUCCESS);
    if(list.number >= -2147483648 && list.number <= 2147483647){
        UT_LOG("number of ecm_dns_svrs is %d which is a valid value.", list.number);
        UT_PASS("dhcpv4c_get_ecm_dns_svrs validation success");
    }
    else{
        UT_LOG("number of ecm_dns_svrs is %d which is a invalid value.", list.number);
        UT_FAIL("dhcpv4c_get_ecm_dns_svrs validation failed");		
    }
    // Perform additional validations on the IP addresses if needed
    for(dns_svrs = 0; dns_svrs < list.number; dns_svrs++){
        memset(ip_str, 0, sizeof(ip_str));
        memset(&addr, 0, sizeof(addr));	
        addr.s_addr = list.addrs[dns_svrs] ;
        strcpy(ip_str,inet_ntoa(addr));
	
        UT_LOG("Return value after modification: %s", ip_str);
    /* Verify IP address falls within valid ranges */
        if(isIpAddressInRange(ip_str,"1.0.0.0","127.0.0.0") || isIpAddressInRange(ip_str,"128.0.0.0","191.255.0.0") || isIpAddressInRange(ip_str,"192.0.0.0","223.255.255.0")){
            UT_LOG("ecm_dns_svrs is %s which is a valid value.", ip_str);
            UT_PASS("dhcpv4c_get_ecm_dns_svrs validation success");
        }
        else{
            UT_LOG("ecm_dns_svrs is %s which is a invalid value.", ip_str);
            UT_FAIL("dhcpv4c_get_ecm_dns_svrs validation failed");
        }
    }
    UT_LOG("Exiting test_l1_dhcpv4c_api_positive1_get_ecm_dns_svrs...");
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

void test_l1_dhcpv4c_api_negative1_get_ecm_dns_svrs(void) {
    UT_LOG("Entering test_l1_dhcpv4c_api_negative1_get_ecm_dns_svrs...");
    UT_LOG("Invoking dhcpv4c_get_ecm_dns_svrs with NULL");
    INT result = dhcpv4c_get_ecm_dns_svrs(NULL);
    UT_LOG("Return status: %d", result);
    UT_ASSERT_EQUAL(result, STATUS_FAILURE);

    UT_LOG("Exiting test_l1_dhcpv4c_api_negative1_get_ecm_dns_svrs...");
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
void test_l1_dhcpv4c_api_positive1_get_ecm_dhcp_svr(void)
{
    char ip_str[20];
    UINT ipValue;
    UT_LOG("Entering test_l1_dhcpv4c_api_positive1_get_ecm_dhcp_svr...");
    UT_LOG("Invoking dhcpv4c_get_ecm_dhcp_svr with valid pointer");
    INT status = dhcpv4c_get_ecm_dhcp_svr(&ipValue);

    UT_LOG("Return Status: %d", status);
    UT_LOG("Output: IP Address - %u",ipValue);
    
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    addr.s_addr = ipValue ;
    strcpy(ip_str,inet_ntoa(addr));
	
    UT_LOG("Return value after modification: %s", ip_str);
    /* Verify IP address falls within valid ranges */
    if(isIpAddressInRange(ip_str,"1.0.0.0","127.0.0.0") || isIpAddressInRange(ip_str,"128.0.0.0","191.255.0.0") || isIpAddressInRange(ip_str,"192.0.0.0","223.255.255.0")){
        UT_LOG("ecm_dhcp_svr is %s which is a valid value.", ip_str);
        UT_PASS("dhcpv4c_get_ecm_dhcp_svr validation success");
    }
    else{
        UT_LOG("ecm_dhcp_svr is %s which is a invalid value.", ip_str);
        UT_FAIL("dhcpv4c_get_ecm_dhcp_svr validation failed");
    }

    UT_LOG("Exiting test_l1_dhcpv4c_api_positive1_get_ecm_dhcp_svr...");
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

void test_l1_dhcpv4c_api_negative1_get_ecm_dhcp_svr(void)
{
    UT_LOG("Entering test_l1_dhcpv4c_api_negative1_get_ecm_dhcp_svr...");
    UT_LOG("Invoking dhcpv4c_get_ecm_dhcp_svr with NULL pointer");
    INT status = dhcpv4c_get_ecm_dhcp_svr(NULL);
    UT_LOG("Return Status: %d", status);

    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG("Exiting test_l1_dhcpv4c_api_negative1_get_ecm_dhcp_svr...");
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
void test_l1_dhcpv4c_api_positive1_get_emta_remain_lease_time(void)
{
    UINT value = 0;
    UT_LOG("Entering test_l1_dhcpv4c_api_positive1_get_emta_remain_lease_time...");
    UT_LOG("Invoking dhcpv4c_get_emta_remain_lease_time with valid memory location");
    INT status = dhcpv4c_get_emta_remain_lease_time(&value);
    
    UT_LOG("Return status: %d", status);
    UT_LOG("Output value: %u", value);
	
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if(value >= 0 && value <= 4294967295){
        UT_LOG("emta_remain_lease_time is %u which is a valid value.", value);
        UT_PASS("dhcpv4c_get_emta_remain_lease_time validation success");
    }
    else{
        UT_LOG("emta_remain_lease_time is %u which is a invalid value.", value);
        UT_FAIL("dhcpv4c_get_emta_remain_lease_time validation failed");		
    }
    
    UT_LOG("Exiting test_l1_dhcpv4c_api_positive1_get_emta_remain_lease_time...");
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
 * | :--------------: | ----------- | --------- | --------------- | ----- |
 * |       01         | Invoking dhcpv4c_get_emta_remain_lease_time with NULL | pValue = NULL | STATUS_FAILURE | Should return STATUS_FAILURE |
 */
void test_l1_dhcpv4c_api_negative1_get_emta_remain_lease_time(void)
{
    UT_LOG("Entering test_l1_dhcpv4c_api_negative1_get_emta_remain_lease_time...");
    UT_LOG("Invoking dhcpv4c_get_emta_remain_lease_time with NULL pointer");
    INT status = dhcpv4c_get_emta_remain_lease_time(NULL);

    UT_LOG("Return status: %d", status);

    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG("Exiting test_l1_dhcpv4c_api_negative1_get_emta_remain_lease_time...");
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

void test_l1_dhcpv4c_api_positive1_dhcpv4c_get_emta_remain_renew_time(void) {
    UINT value;
    UT_LOG("Entering test_l1_dhcpv4c_api_positive1_dhcpv4c_get_emta_remain_renew_time...");
    UT_LOG("Invoking dhcpv4c_get_emta_remain_renew_time with valid pValue");
    INT status = dhcpv4c_get_emta_remain_renew_time(&value);

    UT_LOG("Return status: %d", status);
    UT_LOG("Return value: %u", value);

    UT_ASSERT_EQUAL(STATUS_SUCCESS, status);
    if(value >= 0 && value <= (4294967295)){
        UT_LOG("emta_remain_renew_time is %d which is a valid value.", value);
        UT_PASS("dhcpv4c_get_emta_remain_renew_time validation success");
    }
    else{
        UT_LOG("emta_remain_renew_time is %d which is a invalid value.", value);
        UT_FAIL("dhcpv4c_get_emta_remain_renew_time validation failed");		
    }

    UT_LOG("Exiting test_l1_dhcpv4c_api_positive1_dhcpv4c_get_emta_remain_renew_time...");
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
void test_l1_dhcpv4c_api_negative1_dhcpv4c_get_emta_remain_renew_time(void) {
    UT_LOG("Entering test_l1_dhcpv4c_api_negative1_dhcpv4c_get_emta_remain_renew_time...");
    UT_LOG("Invoking dhcpv4c_get_emta_remain_renew_time with NULL pValue");
    INT status = dhcpv4c_get_emta_remain_renew_time(NULL);

    UT_LOG("Return Status=%d", status);

    UT_ASSERT_EQUAL(STATUS_FAILURE, status);

    UT_LOG("Exiting test_l1_dhcpv4c_api_negative1_dhcpv4c_get_emta_remain_renew_time...");
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

void test_l1_dhcpv4c_api_positive1_get_emta_remain_rebind_time(void)
{
    UINT value;
    UT_LOG("Entering test_l1_dhcpv4c_api_positive1_get_emta_remain_rebind_time...");
    UT_LOG("Invoking dhcpv4c_get_emta_remain_rebind_time with valid output parameter");
    INT status = dhcpv4c_get_emta_remain_rebind_time(&value);

    UT_LOG("Return Status: %d", status);
    UT_LOG("Output Value: %u", value);
    UT_ASSERT_EQUAL(status, STATUS_SUCCESS);
    if(value >= 0 && value <= 4294967295){
        UT_LOG("emta_remain_rebind_time is %u which is a valid value.", value);
        UT_PASS("dhcpv4c_get_emta_remain_rebind_time validation success");
    }
    else{
        UT_LOG("emta_remain_rebind_time is %u which is a invalid value.", value);
        UT_FAIL("dhcpv4c_get_emta_remain_rebind_time validation failed");		
    }

    UT_LOG("Exiting test_l1_dhcpv4c_api_positive1_get_emta_remain_rebind_time...");
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
void test_l1_dhcpv4c_api_negative1_get_emta_remain_rebind_time(void)
{
    UT_LOG("Entering test_l1_dhcpv4c_api_negative1_get_emta_remain_rebind_time...");
    UT_LOG("Invoking dhcpv4c_get_emta_remain_rebind_time with null output parameter");
    INT status = dhcpv4c_get_emta_remain_rebind_time(NULL);

    UT_LOG("Return Status: %d", status);

    UT_ASSERT_EQUAL(status, STATUS_FAILURE);

    UT_LOG("Exiting test_l1_dhcpv4c_api_negative1_get_emta_remain_rebind_time...");
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
    pSuite = UT_add_suite("[L1 dhcpv4c_api]", NULL, NULL);
    if (pSuite == NULL) {
        return -1;
    }
    // List of test function names and strings
   const char* list1[] = {"l1_dhcpv4c_api_positive1_GetValidLeaseTime", "l1_dhcpv4c_api_negative1_InvalidPointer", "l1_dhcpv4c_positive_1_get_ert_remain_lease_time", "l1_dhcpv4c_negative_1_get_ert_remain_lease_time", "l1_dhcpv4c_get_ert_remain_renew_time_positive_1_valid_memory_address_passed", "l1_dhcpv4c_get_ert_remain_renew_time_negative_1_null_pointer_passed", "l1_dhcpv4c_api_positive1_get_ert_remain_rebind_time", "l1_dhcpv4c_api_negative1_get_ert_remain_rebind_time", "l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_config_attempts_validPointer_successfulCall", "l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_config_attempts_nullPointer", "l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_ifname", "l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_ifname", "l1_dhcpv4c_api_positive_1_dhcpv4c_get_ert_fsm_state", "l1_dhcpv4c_api_negative_3_dhcpv4c_get_ert_fsm_state", "l1_dhcpv4c_positive_1_dhcpv4c_get_ert_ip_addr", "l1_dhcpv4c_negative_1_dhcpv4c_get_ert_ip_addr", "l1_dhcpv4c_api_positive_1_get_ert_mask", "l1_dhcpv4c_api_negative_1_get_ert_mask", "l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_gw", "l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_gw", "l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_dns_svrs", "l1_dhcpv4c_api_negative1_invalid_memory_for_dhcpv4c_ip_list_t", "l1_dhcpv4c_api_positive_1_get_ert_dhcp_svr", "l1_dhcpv4c_api_negative_1_dhcpv4c_get_ert_dhcp_svr", "l1_dhcpv4c_api_positive_1_get_ecm_lease_time", "l1_dhcpv4c_api_negative_1_get_ecm_lease_time", "l1_dhcpv4c_positive1_get_ecm_remain_lease_time", "l1_dhcpv4c_negative1_get_ecm_remain_lease_time", "l1_dhcpv4c_get_ecm_remain_renew_time_positive_1_default_case", "l1_dhcpv4c_get_ecm_remain_renew_time_negative_1_null_pointer", "l1_dhcpv4c_api_positive_1_ecm_remain_rebind_time", "l1_dhcpv4c_api_negative_1_get_ecm_remain_rebind_time", "l1_dhcpv4c_api_positive_1_get_ecm_config_attempts", "l1_dhcpv4c_api_negative_1_ecm_config_attempts", "l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_ifname", "l1_dhcpv4c_api_negative1_get_ecm_ifname", "l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_fsm_state", "l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_fsm_state", "l1_dhcpv4c_positive1_GetEcmIpAddress", "l1_dhcpv4c_negative1_GetEcmIpAddress", "l1_dhcpv4c_positive1_get_ecm_mask", "l1_dhcpv4c_negative1_get_ecm_mask", "l1_dhcpv4c_positive1_dhcpv4c_get_ecm_gw_validOutputMemoryAndStatusCheck", "l1_dhcpv4c_negative1_dhcpv4c_get_ecm_gw_nullPointerProvidedForOutputMemory", "l1_dhcpv4c_api_positive1_get_ecm_dns_svrs", "l1_dhcpv4c_api_negative1_get_ecm_dns_svrs", "l1_dhcpv4c_api_positive1_get_ecm_dhcp_svr", "l1_dhcpv4c_api_negative1_get_ecm_dhcp_svr", "l1_dhcpv4c_api_positive1_get_emta_remain_lease_time", "l1_dhcpv4c_api_negative1_get_emta_remain_lease_time", "l1_dhcpv4c_api_positive1_dhcpv4c_get_emta_remain_renew_time", "l1_dhcpv4c_api_negative1_dhcpv4c_get_emta_remain_renew_time", "l1_dhcpv4c_api_positive1_get_emta_remain_rebind_time", "l1_dhcpv4c_api_negative1_get_emta_remain_rebind_time" };
   void (*list2[])() = {test_l1_dhcpv4c_api_positive1_GetValidLeaseTime, test_l1_dhcpv4c_api_negative1_InvalidPointer, test_l1_dhcpv4c_positive_1_get_ert_remain_lease_time, test_l1_dhcpv4c_negative_1_get_ert_remain_lease_time, test_l1_dhcpv4c_get_ert_remain_renew_time_positive_1_valid_memory_address_passed, test_l1_dhcpv4c_get_ert_remain_renew_time_negative_1_null_pointer_passed, test_l1_dhcpv4c_api_positive1_get_ert_remain_rebind_time, test_l1_dhcpv4c_api_negative1_get_ert_remain_rebind_time, test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_config_attempts_validPointer_successfulCall, test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_config_attempts_nullPointer, test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_ifname, test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_ifname, test_l1_dhcpv4c_api_positive_1_dhcpv4c_get_ert_fsm_state, test_l1_dhcpv4c_api_negative_3_dhcpv4c_get_ert_fsm_state, test_l1_dhcpv4c_positive_1_dhcpv4c_get_ert_ip_addr, test_l1_dhcpv4c_negative_1_dhcpv4c_get_ert_ip_addr, test_l1_dhcpv4c_api_positive_1_get_ert_mask, test_l1_dhcpv4c_api_negative_1_get_ert_mask, test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_gw, test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ert_gw, test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ert_dns_svrs, test_l1_dhcpv4c_api_negative1_invalid_memory_for_dhcpv4c_ip_list_t, test_l1_dhcpv4c_api_positive_1_get_ert_dhcp_svr, test_l1_dhcpv4c_api_negative_1_dhcpv4c_get_ert_dhcp_svr, test_l1_dhcpv4c_api_positive_1_get_ecm_lease_time, test_l1_dhcpv4c_api_negative_1_get_ecm_lease_time, test_l1_dhcpv4c_positive1_get_ecm_remain_lease_time, test_l1_dhcpv4c_negative1_get_ecm_remain_lease_time, test_l1_dhcpv4c_get_ecm_remain_renew_time_positive_1_default_case, test_l1_dhcpv4c_get_ecm_remain_renew_time_negative_1_null_pointer, test_l1_dhcpv4c_api_positive_1_ecm_remain_rebind_time, test_l1_dhcpv4c_api_negative_1_get_ecm_remain_rebind_time, test_l1_dhcpv4c_api_positive_1_get_ecm_config_attempts, test_l1_dhcpv4c_api_negative_1_ecm_config_attempts, test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_ifname, test_l1_dhcpv4c_api_negative1_get_ecm_ifname, test_l1_dhcpv4c_api_positive1_dhcpv4c_get_ecm_fsm_state, test_l1_dhcpv4c_api_negative1_dhcpv4c_get_ecm_fsm_state, test_l1_dhcpv4c_positive1_GetEcmIpAddress, test_l1_dhcpv4c_negative1_GetEcmIpAddress, test_l1_dhcpv4c_positive1_get_ecm_mask, test_l1_dhcpv4c_negative1_get_ecm_mask, test_l1_dhcpv4c_positive1_dhcpv4c_get_ecm_gw_validOutputMemoryAndStatusCheck, test_l1_dhcpv4c_negative1_dhcpv4c_get_ecm_gw_nullPointerProvidedForOutputMemory, test_l1_dhcpv4c_api_positive1_get_ecm_dns_svrs, test_l1_dhcpv4c_api_negative1_get_ecm_dns_svrs, test_l1_dhcpv4c_api_positive1_get_ecm_dhcp_svr, test_l1_dhcpv4c_api_negative1_get_ecm_dhcp_svr, test_l1_dhcpv4c_api_positive1_get_emta_remain_lease_time, test_l1_dhcpv4c_api_negative1_get_emta_remain_lease_time, test_l1_dhcpv4c_api_positive1_dhcpv4c_get_emta_remain_renew_time, test_l1_dhcpv4c_api_negative1_dhcpv4c_get_emta_remain_renew_time, test_l1_dhcpv4c_api_positive1_get_emta_remain_rebind_time, test_l1_dhcpv4c_api_negative1_get_emta_remain_rebind_time };
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
