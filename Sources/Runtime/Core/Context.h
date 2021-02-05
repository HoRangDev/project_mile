#pragma once
#include "Core/SubSystem.h"

namespace Mile
{
   /**
    * @brief	��� subsystem ���� �������ִ� ������ subsystem ���� �����̳� �Դϴ�. �������� ����� ��� ���� �ý����� Context��
    *			�����ϰ� �־���ϸ�, ���������� �Ҵ� ���� å�ӵ� ���� �˴ϴ�.
    */
   class MEAPI Context
   {
   public:
      Context();
      ~Context();

   public:
      /**
      * @brief ���ο� Subsystem�� Context�� ����մϴ�.
      * @param newSubSystem ���� ����� Subsystem�� �޸� �ּ�
      */
      void RegisterSubSystem(SubSystem* newSubSystem);
      template <typename T> T* GetSubSystem();

      /**
      * @brief �־��� Ÿ���� Subsystem �� Context�� ��ϵǾ��ִ��� �� �� �ֽ��ϴ�.
      * @return Subsystem ���� ����
      */
      template <typename T> bool HasSubSystem() const;

      void SaveSubSystemConfigs();

   private:
      std::vector<SubSystem*>  m_subSystems;

   };

   template <typename T>
   T* Context::GetSubSystem()
   {
      for (const auto& subSys : m_subSystems)
      {
         T* casted = dynamic_cast<T*>(subSys);
         if (casted != nullptr)
         {
            return casted;
         }
      }

      return nullptr;
   }

   template <typename T>
   bool Context::HasSubSystem() const
   {
      return (GetSubSystem<T>() != nullptr);
   }
}