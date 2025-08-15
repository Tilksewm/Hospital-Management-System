# Hospital Management System

**Contributors:**  
- Tilksew Misganaw
- Bereket Kibret 

---

## 📌 Overview

This **Hospital Management System (HMS)**, implemented in **C++**, was developed as a **Data Structure and Algorithms** course project.  
It demonstrates how core computer science concepts can solve real-world organizational challenges in healthcare by managing:

- **Patient flow**  
- **Doctor assignments**  
- **Department organization**  
- **Medicine inventory**  


---

## 🎯 Objectives

- Automate and optimize hospital workflows.
- Ensure fast, structured access to patient and medicine data.
- Showcase **manual memory management** and **algorithm implementation** in a realistic setting.
- Provide a **command-line interface** for interactive use.

---

## 🏥 Functional Modules

### **Manager**
- Add/remove hospital departments.
- Add/remove/find doctors within departments.
- Generate patient load reports per department.

### **Receptionist**
- Register new patients and create initial appointments.
- Schedule appointments for existing patients by ID.
- Search patient records by name.

### **Assembler**
- Retrieve the next patient awaiting assessment.
- Record vitals (blood pressure, heart rate) and assign priority levels.
- Direct patients to appropriate department queues.

### **Doctor**
- Login with ID to access department appointments.
- View next high-priority patient.
- Access patient history and allergy details.
- Record diagnoses, treatments, and prescriptions.
- Mark appointments complete (moves patient to pharmacy queue).

### **Pharmacist**
- Dispense medicines from prescriptions.
- Add new medicines with name, amount, price, and expiry date.
- View medicine inventory sorted alphabetically (via merge sort).
- Identify the medicine closest to expiry.
- Generate bills including consultation fees and medicine costs.

---

## 🧠 Data Structures & Algorithms

### **Core Data Structures**
- **`std::unordered_map`**
  - Departments: `unordered_map<string, Department>`  
  - Patients: `unordered_map<int, Patient>`  
  > Average O(1) lookups for fast entity access.
  
- **`std::queue`**
  - `preAssemblerQueue` – FIFO processing of new appointments.
  - `pharmacyQueue` – FIFO processing for post-doctor prescriptions.

- **`std::priority_queue`**
  - Department appointment queues sorted by patient priority.

- **Custom Singly Linked List**
  - Stores medicine inventory.
  - Supports add, find, remove, and convert-to-vector operations.
  - Designed for educational demonstration of pointer manipulation.

### **Algorithms**

1. **Merge Sort (Divide & Conquer)**
   - Purpose: Sorts medicine inventory alphabetically by name.
   - Time Complexity: O(N log N), Space Complexity: O(N).
   - Stable sort: Preserves order of equal elements.
   - Applied after converting the linked list to a vector.

2. **Priority Scheduling (`std::priority_queue` with custom comparator)**
   - Purpose: Ensures doctors see higher-priority patients before lower-priority ones.
   - Time Complexity: O(log N) for insertion and removal.
   - Based on `priorityLevel` set during assembler processing.

3. **FIFO Queue Processing (`std::queue`)**
   - Purpose: Manages patient flow in arrival order between Receptionist → Assembler → Pharmacy.
   - Time Complexity: O(1) enqueue/dequeue operations.

4. **Hash Map Lookup (`std::unordered_map`)**
   - Purpose: Stores and retrieves patients, departments, and medicine prices by unique key.
   - Time Complexity: O(1) average-case for search, insert, and delete.

5. **Linear Search in Custom Linked List**
   - Purpose: Locates medicines in inventory by name.
   - Time Complexity: O(N) worst-case.
   - Chosen for educational demonstration of pointer-based traversal and node manipulation.
---

## 🔄 Usage Flow

1. **Receptionist**
   - Registers patients, creates appointments → pushes to `preAssemblerQueue`.

2. **Assembler**
   - Retrieves from `preAssemblerQueue`, records vitals, assigns department → pushes to department’s `priority_queue`.

3. **Doctor**
   - Retrieves from department queue by priority.
   - Updates patient history, creates prescription → pushes to `pharmacyQueue`.

4. **Pharmacist**
   - Retrieves from `pharmacyQueue`, finds medicines in linked list.
   - Dispenses and updates inventory.
   - Optionally sorts inventory using merge sort for display.

---

## 📊 Outputs

Example console outputs include:
- **Patient Load Reports** (by department)
- **Next High-Priority Patient** for doctors
- **Sorted Medicine List** (alphabetical)
- **Next Expiring Medicine** details
- **Final Bill** with itemized costs

---

## 📈 Complexity Analysis

**Time Complexity (average case)**  
- Add/find department: O(1)  
- Add doctor: O(1)  
- Search patient: O(1)  
- Priority queue operations: O(log N)  
- Find medicine: O(M)  
- Sort medicines: O(M log M)  

**Space Complexity**  
- Departments: O(D + ΣND)  
- Patients: O(P + ΣHistory + ΣAllergies)  
- Medicine inventory: O(M)  
- Merge sort auxiliary arrays: O(M)

---

## 🆚 Design Choices

- **Custom Linked List** over `unordered_map` for medicine:
  - Educational focus on pointer operations and manual memory handling.
- **Merge Sort** over Quick Sort:
  - Stable, predictable O(N log N) performance in all cases.

---

## 💻 Sample Run

```text
--- Hospital Management System ---
1) Manager
2) Receptionist
3) Assembler
4) Doctor
5) Pharmacist
6) Exit
Enter your choice: 2

--- Receptionist Menu ---
1) Add new appointment
2) Add existing appointment
3) Search by name
4) Back to Main Menu
Enter your choice: 1
Enter new patient's name: John Doe
Enter age: 45
Enter sex: Male
Enter contact number: +251912345678
New patient registered and appointment added to pre-assembler queue.

Press Enter to continue...

--- Hospital Management System ---
1) Manager
2) Receptionist
3) Assembler
4) Doctor
5) Pharmacist
6) Exit
Enter your choice: 3

Next appointment for assembly:
Patient ID: 102
Name: John Doe
Age: 45
Sex: Male
Contact: +251912345678

Appointment Details:
Registration Time: 2025-08-15 09:42
Priority Level: Not Assigned
Category: Not Assigned

--- Action Menu ---
1) Take this appointment
2) Go back to menu
Enter your choice: 1

--- Assembler Process ---
Record the following details:
Enter priority level (1=highest, 5=lowest): 2
Enter blood pressure: 120
Enter heart rate: 76
Enter category (e.g., Cardiology, Orthopedics): Cardiology

Appointment for patient 'John Doe' has been prioritized and moved to the 'Cardiology' department queue.

Press Enter to continue...

--- Hospital Management System ---
1) Manager
2) Receptionist
3) Assembler
4) Doctor
5) Pharmacist
6) Exit
Enter your choice: 4
Enter doctor ID: 201

Welcome, Dr. Smith (Cardiology)!

Next appointment details:
Patient ID: 102
Name: John Doe
Age: 45
Sex: Male
Contact: +251912345678

Appointment Details:
Priority Level: 2
Category: Cardiology
Blood Pressure: 120
Heart Rate: 76

--- Action Menu ---
1) Take this appointment
2) Go back to menu
Enter your choice: 1

--- Patient Consultation for Dr. Smith ---
Patient ID: 102
Name: John Doe
Age: 45
Sex: Male
Contact: +251912345678

--- Patient History and Allergies ---
Allergies: Unknown
History: Unknown

Record new diagnoses, treatments, and prescriptions:
Diagnosis: Hypertension
Treatment: Beta blockers and lifestyle changes
Prescription list (comma-separated): Atenolol 50mg

Patient records updated. The patient has been sent to the pharmacy.

Press Enter to continue...

--- Hospital Management System ---
1) Manager
2) Receptionist
3) Assembler
4) Doctor
5) Pharmacist
6) Exit
Enter your choice: 5

--- Pharmacist Menu ---
1) Give medicine
2) Record new inventory
3) Get next to expired medicine
4) Display Medicine sorted by name
5) Back to Main Menu
Enter your choice: 1

Patient: John Doe
Prescription: Atenolol 50mg
Dispensing medicine... Done.

Bill generated:
Consultation Fee: 150 ETB
Medicine Cost: 200 ETB
Total: 350 ETB

Press Enter to continue...
