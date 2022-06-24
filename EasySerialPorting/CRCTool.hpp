#pragma once

#include <array>

namespace Easy::Utilities
{
	/**
	 * @brief 冗余校验工具
	 * @author Vincent
	 * @details
	 *  ~ 该静态工具类提供了8位和16位CRC冗余校验计算方法。
	 */
	class CRCTool
	{
	public:
		/// 该工具所使用的8位校验表
		static std::array<unsigned char, 256> CRC8Table;
		/// 该工具所使用的16位校验表
		static std::array<unsigned short, 256> CRC16Table;

		/**
		 * @brief 获取8位CRC校验码
		 * @param data 数据指针
		 * @param length 数据长度
		 * @return 8位CRC校验码
		 */
		static unsigned char GetCRC8CheckSum(const unsigned char* data, unsigned int length,
									   unsigned char initializer = 0xff);

		/**
		 * @brief 获取16位CRC校验码
		 * @param data 数据指针
		 * @param length 数据长度
		 * @return 16位CRC校验码
		 */
		static unsigned short GetCRC16CheckSum(const unsigned char* data, unsigned int length,
										 unsigned short initializer = 0xffff);
	};
}